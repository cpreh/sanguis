#include "object.hpp"
#include "environment.hpp"
#include "sight_range.hpp"
#include "context.hpp"
#include "prop.hpp"
#include "../collision/execute.hpp"
#include "../collision/execute_begin.hpp"
#include "../collision/execute_end.hpp"
#include "../collision/test.hpp"
#include "../collision/satellite.hpp"
#include "../entities/base.hpp"
#include "../entities/movable.hpp"
#include "../entities/with_health.hpp"
#include "../entities/with_dim.hpp"
#include "../message_convert/speed.hpp"
#include "../message_convert/rotate.hpp"
#include "../message_convert/move.hpp"
#include "../message_convert/health.hpp"
#include "../message_convert/experience.hpp"
#include "../../messages/create.hpp"
#include "../../messages/remove.hpp"
#include "../../messages/change_weapon.hpp"
#include "../../messages/give_weapon.hpp"
#include "../../messages/start_attacking.hpp"
#include "../../messages/stop_attacking.hpp"
#include "../../messages/start_reloading.hpp"
#include "../../messages/stop_reloading.hpp"
#include "../../messages/max_health.hpp"
#include "../../load/model/context.hpp"
#include "../../load/model/collection.hpp"
#include "../../load/model/model.hpp"
#include "../../exception.hpp"
#include <sge/math/rect/basic_impl.hpp>
#include <sge/collision/system.hpp>
#include <sge/collision/world.hpp>
#include <sge/time/second.hpp>
#include <sge/time/millisecond.hpp>
#include <sge/make_shared_ptr.hpp>
#include <sge/optional_impl.hpp>
#include <sge/text.hpp>
#include <boost/foreach.hpp>
#include <tr1/functional>

sanguis::server::world::object::object(
	context_ptr const global_context_,
	sge::collision::system_ptr const sys,
	server::environment::load_context_ptr const load_context_
)
:
	global_context_(
		global_context_
	),
	load_context_(
		load_context_
	),
	collision_world_(
		sys->create_world(
			sge::collision::optional_rect(
				sge::collision::rect(
					// FIXME
					-500,
					-500,
					1000,
					1000
				)
			)
		)
	),
	collision_groups_(
		collision_world_
	),
	diff_clock_(),
	send_timer_(
		sge::time::millisecond(
			500
		),
		sge::time::activation_state::active,
		diff_clock_.callback()
	),
	entities_(),
	sight_ranges_(),
	props_(),
	collision_connection_begin_(
		collision_world_->register_begin_callback(
			std::tr1::bind(
				collision::execute,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2,
				collision::execute_begin()
			)
		)
	),
	collision_connection_end_(
		collision_world_->register_end_callback(
			std::tr1::bind(
				collision::execute,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2,
				collision::execute_end()
			)
		)
	),
	collision_connection_test_(
		collision_world_->register_test_callback(
			std::tr1::bind(
				collision::test,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			)
		)
	),
	environment_(
		sge::make_shared_ptr<
			world::environment
		>(
			std::tr1::ref(
				*this
			)
		)
	),
	wave_gen_()
{}

sanguis::server::world::object::~object()
{}

void
sanguis::server::world::object::update(
	time_type const time_
)
{
	diff_clock_.update(
		time_
	);

	wave_gen_.process(
		time_,
		environment(),
		load_context_
	);

	// should we send position updates?
	bool const update_pos = send_timer_.update_b();

	collision_world_->update(
		static_cast<sge::time::funit>(	
			time_
		)
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

		entities::base &e(
			*it->second
		);

		if(
			e.dead()
		)
		{
			// process collision end before the destructor is called
			e.destroy();

			entities_.erase(
				it
			);

			continue;
		}

		e.update(
			static_cast<time_type>(time_)
		);

		if(
			e.type() != entity_type::indeterminate
			&& update_pos
		)
		{
			send_entity_specific(
				e.id(),
				message_convert::rotate(
					e
				)
			);

			{
				entities::with_dim const * const with_dim_(
					dynamic_cast<
						entities::with_dim const *
					>(
						&e
					)
				);

				if(
					with_dim_
				)
					send_entity_specific(
						with_dim_->id(),
						message_convert::move(
							*with_dim_
						)
					);
			}

			{
				entities::movable const *const movable_(
					dynamic_cast<
						entities::movable const *
					>(
						&e
					)
				);

				if(
					movable_
				)
					send_entity_specific(
						movable_->id(),
						message_convert::speed(
							*movable_
						)
					);
			}

			{
				entities::with_health const *const with_health_(
					dynamic_cast<
						entities::with_health const *
					>(
						&e
					)
				);

				if(
					with_health_
				)
					send_entity_specific(
						with_health_->id(),
						message_convert::health(
							*with_health_	
						)
					);
			}
		}
	}
}

sanguis::server::entities::base &
sanguis::server::world::object::insert(
	entities::auto_ptr e,
	entities::insert_parameters const &insert_params
)
{
	entity_id const id(
		e->id()
	);

	e->transfer(
		environment_,
		collision_groups_,
		insert_params
	);

	std::pair<
		entity_map::iterator,
		bool
	> const ret(
		entities_.insert(
			id,
			e
		)
	);

	if(
		!ret.second
	)
		throw exception(
			SGE_TEXT("Double insert of entity!")
		);
	
	return *ret.first->second;
}

sanguis::server::environment::object_ptr const
sanguis::server::world::object::environment() const
{
	return environment_;
}

void
sanguis::server::world::object::weapon_changed(
	entity_id const id,
	weapon_type::type const wt
)
{
	send_entity_specific(
		id,
		messages::create(
			messages::change_weapon(
				id,
				wt
			)
		)
	);
}

void
sanguis::server::world::object::got_weapon(
	entity_id const id,
	weapon_type::type const wt
)
{
	send_entity_specific(
		id,
		messages::create(
			messages::give_weapon(
				id,
				wt
			)
		)
	);
}

void
sanguis::server::world::object::attacking_changed(
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
sanguis::server::world::object::reloading_changed(
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
	/*
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
	*/
}

void
sanguis::server::world::object::pickup_chance(
	probability_type const spawn_chance_,
	pos_type const &center_
)
{
}

void
sanguis::server::world::object::request_transfer(
	world_id const world_id_,
	entity_id const entity_id_,
	entities::insert_parameters const &insert_parameters_
)
{
	entity_map::iterator const it(
		entities_.find(
			entity_id_
		)
	);

	if (
		it == entities_.end()
	)
		throw exception(
			SGE_TEXT("entity can't be transferred!")
		);

	entities::auto_ptr entity_(
		entities_.release(
			it
		).release()
	);

	global_context_->transfer_entity(
		world_id_,
		entity_,
		insert_parameters_
	);
}

void
sanguis::server::world::object::add_sight_range(
	player_id const player_id_,
	entity_id const target_id_
)
{
	sight_ranges_[
		player_id_
	].add(
		target_id_
	);
	
	entity_map::iterator const it(
		entities_.find(
			target_id_
		)
	);

	if(
		it == entities_.end()
	)
		throw exception(
			SGE_TEXT("can't get entity for sight update!")
		);

	entities::base &entity_(
		*it->second
	);

	if(
		entity_.type()
		== entity_type::indeterminate
	)
		return;
			
	send_player_specific(
		player_id_,
		it->second->add_message()
	);
}

void
sanguis::server::world::object::remove_sight_range(
	player_id const player_id_,
	entity_id const target_id_
)
{
	sight_ranges_[
		player_id_
	].remove(
		target_id_
	);
		
	send_player_specific(
		player_id_,
		messages::create(
			messages::remove(
				target_id_
			)
		)
	);
}

void
sanguis::server::world::object::remove_player(
	player_id const player_id_
)
{
	global_context_->remove_player(
		player_id_
	);

	sight_ranges_.erase(
		player_id_
	);
}

sge::collision::world_ptr const
sanguis::server::world::object::collision_world() const
{
	return collision_world_;
}

sanguis::server::environment::load_context_ptr const
sanguis::server::world::object::load_context() const
{
	return load_context_;
}

void
sanguis::server::world::object::send_entity_specific(
	entity_id const id,
	messages::auto_ptr msg
)
{
	BOOST_FOREACH(
		sight_range_map::const_reference range,
		sight_ranges_
	)
		if(
			range.second.contains(
				id
			)
		)
			global_context_->send_to_player(
				range.first,
				msg
			);
}

void
sanguis::server::world::object::send_player_specific(
	player_id const player_id_,
	messages::auto_ptr msg
)
{
	global_context_->send_to_player(
		player_id_,
		msg
	);
}
