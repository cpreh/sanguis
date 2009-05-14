#include "scene.hpp"
#include "entity.hpp"
#include "background.hpp"
#include "factory/client.hpp"
#include "factory/enemy.hpp"
#include "factory/entity.hpp"
#include "factory/friend.hpp"
#include "factory/pickup.hpp"
#include "factory/projectile.hpp"
#include "factory/decoration.hpp"
#include "factory/weapon_pickup.hpp"
#include "coord_transform.hpp"
#include "log.hpp"
#include "environment.hpp"
#include "../messages/unwrap.hpp"
#include "../client_messages/add.hpp"
#include "../client_messages/visible.hpp"
#include "../client/invalid_id.hpp"
#include "../exception.hpp"

#include <sge/make_auto_ptr.hpp>
#include <sge/iconv.hpp>
#include <sge/text.hpp>
#include <sge/format.hpp>
#include <sge/math/dim/structure_cast.hpp>
#include <sge/math/vector/structure_cast.hpp>
#include <sge/log/headers.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/caps.hpp>

// super ugly hack, so that we can use a vector with more than 20 types
// but don't have to touch mpl::vector
#define FUSION_MAX_VECTOR_SIZE 21
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>

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
	sge::font::object &font)
:
	ss(rend),
	hud_(font),
	paused(false),
	env(
		boost::bind(
			&scene::insert,
			this,
			_1),
		resources_,
		system()),
	background_id(
		client::invalid_id),
	paint_background(
		rend->caps().render_target_supported())
{
	if(!paint_background)
		return;
	
	entity_auto_ptr p(
		sge::make_auto_ptr<
			draw::background
		>(
			environment()));
	background_id = p->id();
	insert(p);
}

sanguis::draw::scene::~scene()
{}

void sanguis::draw::scene::process_message(
	messages::base const &m)
{
	messages::unwrap<
		boost::fusion::vector<
			messages::add,
			messages::add_decoration,
			messages::add_enemy,
			messages::add_friend,
			messages::add_pickup,
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
		void
	>(
		*this,
		m,
		boost::bind(
			&scene::process_default_msg,
			this,
			_1
		)
	);
}

void sanguis::draw::scene::client_message(
	client_messages::add const &m)
{
	if(entities.insert(
		m.id(),
		factory::client(
			environment(),
			m,
			system().renderer()->screen_size())).second
	== false)
		throw exception(
			SGE_TEXT("Client object with id already in entity list!")
		);
	// FIXME: configure the object here, too!
}

void sanguis::draw::scene::client_message(
	client_messages::visible const &m)
{
	entity(m.id()).visible(m.get());	
}

void sanguis::draw::scene::draw(
	time_type const delta)
{
	time_type const real_delta =
		paused
		? 0
		: delta;
	
	for(entity_map::iterator it(entities.begin()), next(it); it != entities.end(); it = next)
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
	
	system().render();

	hud_.update(delta);
}

void sanguis::draw::scene::pause(
	bool const p)
{
	paused = p;
}

void sanguis::draw::scene::operator()(
	messages::add const &m)
{
	configure_new_object(
		factory::entity(
			environment(),
			m.get<messages::roles::entity_id>(),
			static_cast<
				entity_type::type
			>(
				m.get<messages::enum_>()
			)
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
	messages::add_decoration const &m)
{
	configure_new_object(
		factory::decoration(
			environment(),
			m.get<messages::roles::entity_id>(),
			static_cast<
				decoration_type::type
			>(
				m.get<messages::roles::decoration>()
			)
		),
		m
	);
}

void sanguis::draw::scene::operator()(
	messages::add_pickup const &m)
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

void sanguis::draw::scene::operator()(
	messages::add_weapon_pickup const &m)
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
			sge::log::_1 << SGE_TEXT("Invalid change_weapon message: Value out of range!"));
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
			ss.renderer()->screen_size(),
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
			SGE_TEXT("Object not in entity map, can't remove it!")
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
		sge::math::dim::structure_cast<
			sge::sprite::dim
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
		sge::math::vector::structure_cast<
			vector2
		>(
			virtual_to_screen(
				ss.renderer()->screen_size(),
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
void sanguis::draw::scene::configure_new_object(
	entity_auto_ptr e_ptr,
	Msg const &m)
{
	entity_id const id(
		m. template get<messages::roles::entity_id>()
	);

	std::pair<entity_map::iterator, bool> const ret(
		entities.insert(
			id,
			e_ptr
		)
	);

	if(ret.second == false)
	{
		SGE_LOG_WARNING(
			log(),
			sge::log::_1
				<< SGE_TEXT("Object with id ")
				<< id
				<< SGE_TEXT(" already in entity list!"));
		return;
	}

	// configure the object
	(*this)(messages::max_health(id, m. template get<messages::roles::max_health>()));
	(*this)(messages::health(id, m. template get<messages::roles::health>()));
	(*this)(messages::move(id, m. template get<messages::pos>()));
	(*this)(messages::resize(id, m. template get<messages::dim>()));
	(*this)(messages::rotate(id, m. template get<messages::roles::angle>()));
	(*this)(messages::speed(id, m. template get<messages::roles::speed>()));
}

void sanguis::draw::scene::render_dead()
{
	sge::renderer::device_ptr const rend(
		system().renderer());

	draw::system temp_sys(rend);
	
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
			background_id));
}

sanguis::draw::environment const &
sanguis::draw::scene::environment()
{
	return env;
}

void sanguis::draw::scene::insert(
	entity_auto_ptr e)
{
	entity_id const id(
		e->id());
	
	if(!entities.insert(
		id,
		e).second
	)
		throw exception(
			SGE_TEXT("scene::insert(): failed to insert!"));
	
}

sanguis::draw::entity &
sanguis::draw::scene::entity(
	entity_id const id)
{
	entity_map::iterator const it = entities.find(id);
	if(it == entities.end())
		throw exception(
			(sge::format(
				SGE_TEXT("Object with id %1% not in entity map!"))
				% id).str());
	return *it->second;
}

sanguis::draw::entity const &
sanguis::draw::scene::entity(
	entity_id const id) const
{
	return const_cast<draw::entity const &>(
		const_cast<scene &>(*this).entity(id));
}

void sanguis::draw::scene::process_default_msg(
messages::base const &m)
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1
			<< SGE_TEXT("Invalid message event in scene: ")
			<< sge::iconv(typeid(m).name()));
}

sanguis::draw::system &
sanguis::draw::scene::system()
{
	return ss;
}

sge::log::logger &
sanguis::draw::scene::log()
{
	static sge::log::logger log_(
		draw::log(),
		SGE_TEXT("scene: "),
		true
	);
	return log_;
}
