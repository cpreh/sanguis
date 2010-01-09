#include "object.hpp"
#include "z_ordering.hpp"
#include "factory/client.hpp"
#include "sprite/order.hpp"
#include "../messages/call/object.hpp"
#include "../messages/role_name.hpp"
#include "../client_messages/add.hpp"
#include "../client_messages/visible.hpp"
#include "../client/invalid_id.hpp"
#include "../exception.hpp"
#include "../load/context.hpp"

#include <sge/renderer/device.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/sprite/default_equal.hpp>
#include <sge/sprite/intrusive/system_impl.hpp>
#include <sge/sprite/object_impl.hpp>

#include <fcppt/function/object.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_auto_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/format.hpp>

#include <boost/foreach.hpp>

#include <utility>

sanguis::client::draw2d::scene::object::object(
	load::context const &resources_,
	sge::renderer::device_ptr const rend_,
	sge::font::object &font
)
:
	resources_(resources_),
	rend_(rend_),
	normal_system_(rend),
	colored_system_(rend),
	client_system_(rend),
	particle_system_(rend),
	hud_(font),
	paused_(false),
	transform_callback_(
		std::tr1::bind(
			&object::transform,
			this,
			std::tr1::placeholders::_1
		)
	),
	insert_callback_(
		std::tr1::bind(
			&object::insert,
			this,
			std::tr1::placeholders::_1
		)
	),
	message_environment_(
		fcppt::make_auto_ptr<
			message_environment
		>(
			std::tr1::ref(
				*this
			)
		)
	),
	control_environment_(
		fcppt::make_auto_ptr<
			control_environment
		>(
			std::tr1::ref(
				*this
			)
		)
	),
	message_dispatcher_(
		fcppt::make_auto_ptr<
			message::dispatcher
		>(
			std::tr1::ref(
				*message_environment_
			)
		)
	),
	entities_()
{}

sanguis::client::draw2d::scene::object::~object()
{}

void
sanguis::client::draw2d::scene::object::process_message(
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
		message_dispatcher_,
		std::tr1::bind(
			&message_dispatcher::process_default_msg,
			&message_dispatcher_,
			std::tr1::placeholders::_1
		)
	);
}

void
sanguis::client::draw2d::scene::object::client_message(
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

void
sanguis::client::draw2d::scene::object::client_message(
	client_messages::visible const &m
)
{
	entity(m.id()).visible(m.get());	
}

void
sanguis::client::draw2d::scene::object::draw(
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
		entity_map::iterator it(
			entities.begin()
		),
		next(it);
		it != entities.end();
		it = next
	)
	{
		++next;

		draw::entity &e = *it->second;

		e.update(
			real_delta
		);

		if(
			e.may_be_removed()
		)
		{
			e.on_remove();

			entities.erase(it);
		}
	}

	BOOST_FOREACH(
		entity_map::reference r,
		dead_list
	)
		r.second->update(
			real_delta
		);
	
	render_systems();

	hud_.update(
		delta
	);
}

void
sanguis::client::draw2d::scene::object::pause(
	bool const p
)
{
	paused = p;
}

void
sanguis::client::draw2d::scene::render_systems()
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

sanguis::draw::entity &
sanguis::client::draw2d::scene::object::insert(
	entity_auto_ptr e,
	entity_id const id
)
{
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
sanguis::client::draw2d::scene::object::entity(
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
				fcppt::format(
					FCPPT_TEXT("Object with id %1% not in entity map!")
				)
				% id
			).str()
		);
	return *it->second;
}

sanguis::draw::entity const &
sanguis::client::draw2d::scene::object::entity(
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

sanguis::client::draw2d::entities::base &
sanguis::client::draw2d::scene::object::own_player()
{
	return entity(
		player_id_
	);
}

void
sanguis::client::draw2d::scene::object::transform(
	sprite::point const &center_
)
{
	sprite::matrix const matrix_(
		fcppt::math::matrix::translate(
			fcppt::math::vector::construct(
				center_,
				0
			)
		)
	);

	normal_system_.transform(		
		matrix_
	);
}

sanguis::client::draw2d::draw2d::transform_callback const &
sanguis::client::draw2d::scene::object::transform_callback() const
{
	return transform_callback_;	
}

sanguis::client::draw2d::draw2d::insert_callback const &
sanguis::client::draw2d::scene::object::insert_callback() const
{
	return insert_callback_;
}

sanguis::client::draw2d::sprite::normal::system &
sanguis::client::draw2d::scene::object::normal_system()
{
	return normal_system_;
}

sanguis::client::draw2d::sprite::colored::system &
sanguis::client::draw2d::scene::object::colored_system()
{
	return colored_system_;
}

sanguis::client::draw2d::sprite::client::system &
sanguis::client::draw2d::scene::object::client_system()
{
	return client_system_;
}

sanguis::client::draw2d::sprite::particle::system &
sanguis::client::draw2d::scene::object::particle_system()
{
	return particle_system_;
}

sanguis::load::model::collection const &
sanguis::client::draw2d::scene::object::load_collection() const
{
	return resources_.models()();
}
