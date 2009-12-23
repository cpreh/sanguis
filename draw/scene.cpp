#include "scene.hpp"
#include "entity.hpp"
#include "background.hpp"
#include "configure_entity.hpp"
#include "log.hpp"
#include "environment.hpp"
#include "z_ordering.hpp"
#include "factory/aoe_projectile.hpp"
#include "factory/client.hpp"
#include "factory/enemy.hpp"
#include "factory/friend.hpp"
#include "factory/pickup.hpp"
#include "factory/player.hpp"
#include "factory/projectile.hpp"
#include "factory/weapon_pickup.hpp"
#include "coord_transform.hpp"
#include "sprite/order.hpp"
#include "../messages/call/object.hpp"
#include "../messages/role_name.hpp"
#include "../client_messages/add.hpp"
#include "../client_messages/visible.hpp"
#include "../client/invalid_id.hpp"
#include "../exception.hpp"
#include "../load/context.hpp"

#include <fcppt/make_auto_ptr.hpp>
#include <sge/iconv.hpp>
#include <fcppt/text.hpp>
#include <sge/format.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/log/object.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/caps.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/target.hpp>
#include <sge/renderer/const_scoped_target_lock.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/sprite/default_equal.hpp>
#include <sge/sprite/intrusive/system_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <fcppt/function/object.hpp>

#include <majutsu/is_role.hpp>

#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector/vector30.hpp>
#include <boost/foreach.hpp>

#include <tr1/functional>

#include <utility>
#include <typeinfo>
#include <ostream>

namespace
{

unsigned const render_dead_amount = 20;

}

sanguis::draw::scene::scene(
	load::context const &resources_,
	sge::renderer::device_ptr const rend,
	sge::font::object &font
)
:
	rend(rend),
	normal_system_(rend),
	colored_system_(rend),
	client_system_(rend),
	particle_system_(rend),
	hud_(font),
	paused(false),
	env(
		std::tr1::bind(
			&scene::insert,
			this,
			std::tr1::placeholders::_1
		),
		resources_,
		colored_system_,
		normal_system_,
		client_system_,
		particle_system_
	),
	background_id(
		client::invalid_id
	),
	paint_background(
		rend->caps().render_target_supported()
	)
{
	if(!paint_background)
		return;
	
	entity_auto_ptr p(
		fcppt::make_auto_ptr<
			draw::background
		>(
			environment()
		)
	);

	background_id = p->id();
	insert(p);
}

sanguis::draw::scene::~scene()
{}

void
sanguis::draw::scene::process_message(
	messages::base const &m
)
{
	static messages::call::object<
		boost::mpl::vector21<
			messages::add_aoe_projectile,
			messages::add_enemy,
			messages::add_friend,
			messages::add_pickup,
			messages::add_player,
			messages::add_projectile,
			messages::add_weapon_pickup,
			messages::change_weapon,
			messages::experience,
			messages::health,
			messages::level_up,
			messages::max_health,
			messages::move,
			messages::remove,
			messages::resize,
			messages::rotate,
			messages::start_attacking,
			messages::stop_attacking,
			messages::start_reloading,
			messages::stop_reloading,
			messages::speed
		>,
		scene
	> dispatcher;

	dispatcher(
		m,
		*this,
		std::tr1::bind(
			&scene::process_default_msg,
			this,
			std::tr1::placeholders::_1
		)
	);
}

void
sanguis::draw::scene::client_message(
	client_messages::add const &m
)
{
	if(
		entities.insert(
			m.id(),
			factory::client(
				environment(),
				m,
				rend->screen_size()
			)
		).second
		== false
	)
		throw exception(
			FCPPT_TEXT("Client object with id already in entity list!")
		);
	// FIXME: configure the object here, too!
}

void sanguis::draw::scene::client_message(
	client_messages::visible const &m)
{
	entity(m.id()).visible(m.get());	
}

void
sanguis::draw::scene::draw(
	time_type const delta
)
{
	time_type const real_delta =
		paused
		? 0
		: delta;
	
	env.context().update(
		real_delta
	);
	
	for(
		entity_map::iterator it(entities.begin()), next(it);
		it != entities.end();
		it = next
	)
	{
		draw::entity &e = *it->second;
		++next;

		e.update(real_delta);

		if(e.may_be_removed())
		{
			e.on_remove();
			if(e.remove_action() == draw::remove_action::render_dead)
				dead_list.transfer(
					it,
					entities
				);
			else
				entities.erase(it);
		}
	}

	BOOST_FOREACH(entity_map::reference r, dead_list)
		r.second->update(real_delta);
	
	if(dead_list.size() >= render_dead_amount)
		render_dead();

	{
	sge::renderer::state::scoped const state_(
		rend,	
		sge::sprite::render_states()
	);

	normal_system_.matrices();

	client_system_.render(
		z_ordering::background,
		sge::sprite::default_equal()
	);
		
	for(
		sprite::order index(
			z_ordering::corpses
		);
		index < z_ordering::healthbar_lower;
		++index
	)
		normal_system_.render(
			index,
			sge::sprite::default_equal()
		);
	
	for(
		sprite::order index(
			z_ordering::healthbar_lower
		);
		index < z_ordering::smoke;
		++index
	)
		colored_system_.render(
			index,
			sge::sprite::default_equal()
		);

	for(
		sprite::order index(
			z_ordering::smoke
		);
		index < z_ordering::cursor;
		++index
	)
		particle_system_.render(
			index,
			sge::sprite::default_equal()
		);

	client_system_.render(
		z_ordering::cursor,
		sge::sprite::default_equal()
	);

	}

	hud_.update(delta);
}

sge::renderer::texture_ptr const
sanguis::draw::scene::capture_screen()
{
	{
		sge::renderer::scoped_block const block_(
			rend
		);

		normal_system_.render_all(
			sge::sprite::default_equal()
		);
	}

	return rend->create_texture(
		sge::renderer::const_scoped_target_lock(
			rend->target()
		).value(),
		sge::renderer::filter::linear,
		sge::renderer::resource_flags::none
	);
}

void sanguis::draw::scene::pause(
	bool const p)
{
	paused = p;
}

void sanguis::draw::scene::operator()(
	messages::add_aoe_projectile const &m)
{
	configure_new_object(
		factory::aoe_projectile(
			environment(),
			m.get<messages::roles::entity_id>(),
			static_cast<
				aoe_projectile_type::type
			>(
				m.get<messages::roles::aoe_projectile>()
			),
			m.get<messages::roles::aoe>()
		),
		m
	);
}

void sanguis::draw::scene::operator()(
	messages::add_enemy const &m)
{
	configure_new_object(
		factory::enemy(
			environment(),
			m.get<messages::roles::entity_id>(),
			static_cast<
				enemy_type::type
			>(
				m.get<messages::roles::enemy>()
			)
		),
		m
	);
}

void sanguis::draw::scene::operator()(
	messages::add_friend const &m)
{
	configure_new_object(
		factory::friend_(
			environment(),
			m.get<messages::roles::entity_id>(),
			static_cast<
				friend_type::type
			>(
				m.get<messages::roles::friend_>()
			)
		),
		m
	);
}

void sanguis::draw::scene::operator()(
	messages::add_pickup const &m
)
{
	configure_new_object(
		factory::pickup(
			environment(),
			m.get<messages::roles::entity_id>(),
			static_cast<
				pickup_type::type
			>(
				m.get<messages::roles::pickup>()
			)
		),
		m
	);
}

void sanguis::draw::scene::operator()(
	messages::add_player const &m
)
{
	configure_new_object(
		factory::player(
			environment(),
			m.get<messages::roles::entity_id>()
		),
		m
	);
}

void sanguis::draw::scene::operator()(
	messages::add_projectile const &m)
{
	configure_new_object(
		factory::projectile(
			environment(),
			m.get<messages::roles::entity_id>(),
			static_cast<
				projectile_type::type
			>(
				m.get<messages::roles::projectile>()
			)
		),
		m
	);
}

void
sanguis::draw::scene::operator()(
	messages::add_weapon_pickup const &m
)
{
	configure_new_object(
		factory::weapon_pickup(
			environment(),
			m.get<messages::roles::entity_id>(),
			static_cast<
				weapon_type::type
			>(
				m.get<messages::roles::weapon>()
			)
		),
		m
	);
}

void sanguis::draw::scene::operator()(
	messages::change_weapon const &m)
{
	messages::types::enum_ const value(
		m.get<messages::roles::weapon>()
	);
	
	if(value >= static_cast<messages::types::enum_>(weapon_type::size))
	{
		SGE_LOG_WARNING(
			log(),
			fcppt::log::_ << FCPPT_TEXT("Invalid change_weapon message: Value out of range!"));
		return;
	}
	
	entity(m.get<messages::roles::entity_id>()).weapon(
		static_cast<weapon_type::type>(
			value
		)
	);
}

void sanguis::draw::scene::operator()(
	messages::experience const &m)
{
	hud_.experience(
		m.get<messages::roles::experience>()
	);
}

void sanguis::draw::scene::operator()(
	messages::health const &m)
{
	entity(
		m.get<messages::roles::entity_id>()
	).health(
		m.get<messages::roles::health>()
	);
}

void sanguis::draw::scene::operator()(
	messages::level_up const &m)
{
	hud_.level(
		m.get<messages::level_type>()
	);
}

void sanguis::draw::scene::operator()(
	messages::max_health const &m)
{
	entity(
		m.get<messages::roles::entity_id>()
	).max_health(
		m.get<messages::roles::max_health>()
	);
}

void sanguis::draw::scene::operator()(
	messages::move const &m)
{
	entity(
		m.get<messages::roles::entity_id>()
	).pos(
		virtual_to_screen(
			rend->screen_size(),
			m.get<messages::pos>()
		)
	);
}

void sanguis::draw::scene::operator()(
	messages::remove const &m)
{
	entity_map::iterator const it(
		entities.find(
			m.get<messages::roles::entity_id>()
		)
	);

	if(it == entities.end())
		throw exception(
			FCPPT_TEXT("Object not in entity map, can't remove it!")
		);
	
	draw::entity &e(
		*it->second
	);

	e.decay();
}

void sanguis::draw::scene::operator()(
	messages::resize const &m)
{
	//entity(m.id()).dim(virtual_to_screen(ss.renderer()->screen_size(), m.dim()));
	entity(
		m.get<messages::roles::entity_id>()
	).dim(
		fcppt::math::dim::structure_cast<
			sprite::dim
		>(
			m.get<messages::dim>()
		)
	);
}

void sanguis::draw::scene::operator()(
	messages::rotate const &m)
{
	entity(
		m.get<messages::roles::entity_id>()
	).orientation(
		m.get<messages::roles::angle>()
	);
}

void sanguis::draw::scene::operator()(
	messages::speed const &m)
{
	entity(
		m.get<messages::roles::entity_id>()
	).speed(
		fcppt::math::vector::structure_cast<
			vector2
		>(
			virtual_to_screen(
				rend->screen_size(),
				m.get<messages::roles::speed>()
			)
		)
	);
}

void sanguis::draw::scene::operator()(
	messages::start_attacking const &m)
{
	entity(
		m.get<messages::roles::entity_id>()
	).start_attacking();
}

void sanguis::draw::scene::operator()(
	messages::stop_attacking const &m)
{
	entity(
		m.get<messages::roles::entity_id>()
	).stop_attacking();
}

void sanguis::draw::scene::operator()(
	messages::start_reloading const &m)
{
	entity(
		m.get<messages::roles::entity_id>()
	).start_reloading();
}

void sanguis::draw::scene::operator()(
	messages::stop_reloading const &m)
{
	entity(
		m.get<messages::roles::entity_id>()
	).stop_reloading();
}

template<
	typename Msg
>
void
sanguis::draw::scene::configure_new_object(
	entity_auto_ptr e_ptr,
	Msg const &m
)
{
	draw::entity &entity_(
		insert(
			e_ptr
		)
	);

	boost::mpl::for_each<
		boost::mpl::transform_view<
			boost::mpl::filter_view<
				typename Msg::memory_type::types,
				majutsu::is_role<
					boost::mpl::_1
				>
			>,
			messages::role_name<
				boost::mpl::_1
			>
		>
	>(
		configure_entity<
			Msg
		>(
			*this,
			entity_.id(),
			m
		)
	);
}

void sanguis::draw::scene::render_dead()
{
	sprite::normal::system temp_sys(rend);
	
	BOOST_FOREACH(entity_map::reference r, dead_list)
		r.second->transfer(
			temp_sys
		);
	
	if(paint_background)
		background().paint_dead(
			temp_sys
		);
	
	dead_list.clear();
}

sanguis::draw::background &
sanguis::draw::scene::background()
{
	return dynamic_cast<
		draw::background &
	>(
		entity(
			background_id
		)
	);
}

sanguis::draw::environment const &
sanguis::draw::scene::environment()
{
	return env;
}

sanguis::draw::entity &
sanguis::draw::scene::insert(
	entity_auto_ptr e
)
{
	entity_id const id(
		e->id()
	);
	
	std::pair<
		entity_map::iterator,
		bool
	> const ret(
		entities.insert(
			id,
			e
		)
	);

	if(
		!ret.second
	)
		throw exception(
			FCPPT_TEXT("scene::insert(): failed to insert!")
		);
	
	return *ret.first->second;
}

sanguis::draw::entity &
sanguis::draw::scene::entity(
	entity_id const id
)
{
	entity_map::iterator const it(
		entities.find(
			id
		)
	);

	if(
		it == entities.end()
	)
		throw exception(
			(
				sge::format(
					FCPPT_TEXT("Object with id %1% not in entity map!")
				)
				% id
			).str()
		);
	return *it->second;
}

sanguis::draw::entity const &
sanguis::draw::scene::entity(
	entity_id const id
) const
{
	return
		const_cast<
			draw::entity const &
		>(
			const_cast<
				scene &
			>(
				*this
			).entity(
				id
			)
		);
}

void
sanguis::draw::scene::process_default_msg(
	messages::base const &m
)
{
	SGE_LOG_WARNING(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("Invalid message event in scene: ")
			<< sge::iconv(typeid(m).name()));
}

fcppt::log::object &
sanguis::draw::scene::log()
{
	static fcppt::log::object log_(
		fcppt::log::parameters::inherited(
			draw::log(),
			FCPPT_TEXT("scene")
		)
	);
	return log_;
}
