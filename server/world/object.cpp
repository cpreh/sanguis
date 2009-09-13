#include "object.hpp"
#include "environment.hpp"
#include "context.hpp"
#include "../collision/execute.hpp"
#include "../collision/test.hpp"
#include "../message_convert/speed.hpp"
#include "../message_convert/rotate.hpp"
#include "../message_convert/remove.hpp"
#include "../message_convert/move.hpp"
#include "../message_convert/health.hpp"
#include "../../messages/create.hpp"
#include "../../exception.hpp"
#include <sge/collision/system.hpp>
#include <sge/collision/world.hpp>
#include <sge/time/second.hpp>
#include <sge/make_shared_ptr.hpp>
#include <sge/text.hpp>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>

sanguis::server::world::object::object(
	context_ptr const global_context_,
	sge::collision::system_ptr const sys
)
:
	collision_world_(
		sys->create_world(
			// TODO
		)
	),
	diff_clock_(),
	sight_range_timer_(
		sge::time::second(
			10
		),
		sge::time::activation_state::active,
		diff_clock_.callback()
	),
	entities_(),
	props_(),
	collision_test_connection_(
		collision_world_->test_callback(
			boost::bind(
				collision::test,
				_1,
				_2
			)
		)
	),
	collision_connection_(
		collision_world_->register_callback(
			boost::bind(
				collision::execute,
				_1,
				_2
			)
		)
	),
	callbacks_(
		sge::make_shared_ptr<
			environment
		>(
			*this
		)
	)
{}

sanguis::server::world::object::~object()
{}

void
sanguis::server::world::object::update(
	time_type const time_
)
{
	if(
		sight_range_timer_.update()
	)
		BOOST_FOREACH(
			sight_range_map::reference ref,
			sight_ranges_
		)
			ref.update(
				time_
			);

	// should we send position updates?
	bool const update_pos = send_timer.update_b();

	collision_world_->update(
		static_cast<sge::time::funit>(delta)
	);

	for (
		entity_map::iterator it(
			entities_.begin()
		),
		next(
			it
		);
		it != entities_.end();
		it = next
	)
	{
		++next;

		entities::entity &e(
			it->second
		);

		/*
		if(
			!e.active()
		)
			continue;
		*/

		if(
			e.dead()
		)
		{
			if(e.type() != entity_type::indeterminate)
			{
				send_entity_specific(
					e.id(),
					message_convert::health(e)
				);

				send_entity_specific(
					e.id(),
					message_convert::remove(e)
				);
			}
			
			entities.erase(it);

			continue;
		}

		e.update(
			static_cast<time_type>(delta)
		);

		if(
			e.type() != entity_type::indeterminate
			&& update_pos
		)
		{
			send_entity_specific(
				e.id(),
				message_convert::move(
					e
				)
			);

			send_entity_specific(
				e.id(),
				message_convert::speed(
					e
				)
			);

			send_entity_specific(
				e.id(),
				message_convert::rotate(
					e
				)
			);

			if(
				e.update_health()
			)
				send_entity_specific(
					e.id(),
					message_convert::health(
						e
					)
				);
		}
	}
}

void
sanguis::server::world::weapon_changed(
	entity_id const id,
	weapon_type::type const wt
)
{
	send_entity_specific(
		id,
		messages::weapon_changed(
			id,
			wt
		)
	);
}

void
sanguis::server::world::got_weapon(
	entity_id const id,
	weapon_type::type const wt
)
{
	send_player_specific(
		id,
		messages::create(
			messages::got_weapon(
				wt
			)
		)
	);
}

void
sanguis::server::world::attacking_changed(
	entity_id const id,
	bool const is_attacking
)
{
	send_entity_specific(
		id,
		is_attacking
		?
			messages::create(
				messages::start_attacking(
					id
				)
			)
		:
			messages::create(
				messages::stop_attacking(
					id
				)
			)
	);
}

void
sanguis::server::world::reloading_changed(
	entity_id const id,
	bool const is_reloading
)
{
	send_entity_specific(
		id,
		is_reloading
		?
			messages::create(
				messages::start_reloading(
					id
				)
			)
		:
			messages::create(
				messages::stop_reloading(
					id
				)
			)
	);
}

void
sanguis::server::world::object::max_health_changed(
	entity_id const id,
	health_type const health_
)
{
	send_entity_specific(
		id,
		messages::create(
			messages::max_health(
				id,
				health_
			)
		)
	);
}

void
sanguis::server::world::object::divide_exp(
	exp_type const exp_
)
{
	if(
		sge::math::almost_zero(
			exp_
		)
	)
		return;

	BOOST_FOREACH(
		player_map::reference ref,
		players_
	)
	{
		entities::player &p = *ref.second;
		p.exp(p.exp() + exp);

		send()(message_convert::experience(p));
	}
}

void
sanguis::server::world::object::request_transfer(
	world_id const world_id_,
	entity_id const entity_id_
)
{
	entity_map::iterator it const(
		entities_.find(
			entity_id
		)
	);

	if (
		it == entities_.end()
	)
		throw exception(
			SGE_TEXT("entity can't be transferred!")
		);

	global_context_->transfer_entity(
		world_id_,
		entities_.release(
			it
		)
	);
}
void
sanguis::server::world::update_sight_range(
	player_id const player_id_,
	entity_id const target_id_
)
{
	sight_range &range(
		sight_ranges_[
			player_id_
		]
	);

	if(
		range.add(
			target_id_
		)
	)
		send_player_specific(
			player_id_,
			entities_[
				target_id_
			]->add_message()
		);
}

void
sanguis::server::world::remove_player(
	player_id_ const player_id_
)
{
	global_context_->remove_player(
		player_id_
	);
}

sanguis::server::entities::entity &
sanguis::server::world::object::insert_entity(
	entities::auto_ptr e
)
{
	entity_id const id(
		e->id()
	);

	e.environment(
		environment_
	);

	return 
		*entities_.insert(
			id,
			e
		).second;
}

sge::collision::world_ptr const
sanguis::server::world::object::collision_world() const
{
	return collision_world_;
}

void
sanguis::server::world::object::send_entity_specific(
	entity_id const id,
	messages::auto_ptr msg
)
{
	BOOST_FOREACH(
		sight_range_list::const_reference range,
		sight_ranges
	)
		if(
			range.contains(
				range
			)
		)
			global_context_->send_to_player(
				range.player_id(),
				msg
			);
}

void
sanguis::server::world::object::send_player_specific(
	entity_id const player_id,
	messages::auto_ptr msg
)
{
	global_context_->send_to_player(
		player_id,
		msg
	);
}
