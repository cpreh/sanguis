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
#include <fcppt/iconv.hpp>
#include <fcppt/text.hpp>
#include <fcppt/format.hpp>
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
	message_dispatcher(
		
	)
{}

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
		message_dispatcher_,
		std::tr1::bind(
			&message_dispatcher::process_default_msg,
			&message_dispatcher_,
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

void
sanguis::draw::scene::client_message(
	client_messages::visible const &m
)
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
sanguis::draw::scene::pause(
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
sanguis::draw::scene::insert(
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
				fcppt::format(
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
