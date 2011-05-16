#include "object.hpp"
#include "context.hpp"
#include "create_static_body.hpp"
#include "environment.hpp"
#include "sight_range.hpp"
#include "../collision/body_collision.hpp"
#include "../entities/base.hpp"
#include "../entities/with_health.hpp"
#include "../entities/with_velocity.hpp"
#include "../entities/player.hpp"
#include "../message_convert/speed.hpp"
#include "../message_convert/rotate.hpp"
#include "../message_convert/move.hpp"
#include "../message_convert/health.hpp"
#include "../../messages/change_weapon.hpp"
#include "../../messages/change_world.hpp"
#include "../../messages/create.hpp"
#include "../../messages/die.hpp"
#include "../../messages/experience.hpp"
#include "../../messages/give_weapon.hpp"
#include "../../messages/level_up.hpp"
#include "../../messages/remove.hpp"
#include "../../messages/start_attacking.hpp"
#include "../../messages/start_reloading.hpp"
#include "../../messages/stop_attacking.hpp"
#include "../../messages/stop_reloading.hpp"
#include "../../messages/max_health.hpp"
#include "../../messages/types/exp.hpp"
#include "../../load/model/context.hpp"
#include "../../load/model/collection.hpp"
#include "../../load/model/object.hpp"
#include "../../exception.hpp"
#include "../../time_to_second.hpp"
#include <sanguis/creator/generator/result.hpp>
#include <sge/projectile/body/object.hpp>
#include <sge/projectile/time_increment.hpp>
#include <sge/projectile/world.hpp>
#include <sge/time/second_f.hpp>
#include <sge/time/millisecond.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/utf8/convert.hpp>
#include <fcppt/try_dynamic_cast.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/format.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>

sanguis::server::world::object::object(
	sanguis::world_id const _id,
	world::context &_global_context,
	server::environment::load_context &_load_context,
	server::console &_console,
	sanguis::creator::generator::result const &_generated_world
)
:
	id_(_id),
	seed_(
		_generated_world.seed()
	),
	generator_name_(
		_generated_world.name()
	),
	size_(
		_generated_world.size()
	),
	global_context_(
		_global_context
	),
	load_context_(
		_load_context
	),
	collision_world_(
		fcppt::make_unique_ptr<
			sge::projectile::world
		>()
	),
	collision_groups_(
		*collision_world_
	),
	collision_connection_(
		collision_world_->body_collision(
			std::tr1::bind(
				&collision::body_collision,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			)
		)
	),
	sight_ranges_(),
	diff_clock_(),
	send_timer_(
		sge::time::millisecond(
			500
		),
		sge::time::activation_state::active,
		diff_clock_.callback()
	),
	environment_(
		fcppt::make_unique_ptr<
			world::environment
		>(
			fcppt::ref(
				*this
			)
		)
	),
	entities_(),
	pickup_spawner_(
		*environment_
	),
	wave_gen_(
		_console
	),
	static_body_(
		world::create_static_body(
			_generated_world.shapes()
		)
	)
{
}

sanguis::server::world::object::~object()
{
}

void
sanguis::server::world::object::update(
	sanguis::time_delta const &_time
)
{
	diff_clock_.update(
		_time
	);

	wave_gen_.process(
		_time,
		this->environment(),
		load_context_
	);

	// should we send position updates?
	bool const update_pos(
		send_timer_.update_b()
	);

	collision_world_->update(
		sge::projectile::time_increment(
			sge::time::second_f(
				sanguis::time_to_second(
					_time
				)
			)
		)
	);

	for(
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

		this->update_entity(
			it,
			_time,
			update_pos
		);
	}
}

void
sanguis::server::world::object::insert(
	entities::unique_ptr _entity,
	entities::insert_parameters const &_insert_parameters
)
{
	entity_id const id(
		_entity->id()
	);

	typedef std::pair<
		entity_map::iterator,
		bool
	> return_type;
	
	return_type const ret(
		entities_.insert(
			id,
			move(
				_entity
			)
		)
	);

	if(
		!ret.second
	)
		throw sanguis::exception(
			FCPPT_TEXT("Double insert of entity!")
		);

	ret.first->second->transfer(
		this->environment(),
		collision_groups_,
		_insert_parameters
	);

	FCPPT_TRY_DYNAMIC_CAST(
		entities::player const *,
		player_ret,
		ret.first->second
	)
		this->send_player_specific(
			player_ret->player_id(),
			messages::create(
				messages::change_world(
					id_,
					seed_,
					fcppt::utf8::convert(
						generator_name_.get()
					),
					size_
				)
			)
		);
}

sanguis::server::environment::object &
sanguis::server::world::object::environment() const
{
	return *environment_;
}

void
sanguis::server::world::object::weapon_changed(
	sanguis::entity_id const _id,
	weapon_type::type const _wt
)
{
	this->send_entity_specific(
		_id,
		messages::create(
			messages::change_weapon(
				_id,
				_wt
			)
		)
	);
}

void
sanguis::server::world::object::got_weapon(
	server::player_id const _player_id,
	sanguis::entity_id const _entity_id,
	weapon_type::type const _wt
)
{
	this->send_player_specific(
		_player_id,
		messages::create(
			messages::give_weapon(
				_entity_id,
				_wt
			)
		)
	);
}

void
sanguis::server::world::object::attacking_changed(
	sanguis::entity_id const _id,
	bool const _is_attacking
)
{
	this->send_entity_specific(
		_id,
		_is_attacking
		?
			messages::create(
				messages::start_attacking(
					_id
				)
			)
		:
			messages::create(
				messages::stop_attacking(
					_id
				)
			)
	);
}

void
sanguis::server::world::object::reloading_changed(
	sanguis::entity_id const _id,
	bool const _is_reloading
)
{
	this->send_entity_specific(
		_id,
		_is_reloading
		?
			messages::create(
				messages::start_reloading(
					_id
				)
			)
		:
			messages::create(
				messages::stop_reloading(
					_id
				)
			)
	);
}

void
sanguis::server::world::object::max_health_changed(
	sanguis::entity_id const _id,
	server::health const _health
)
{
	this->send_entity_specific(
		_id,
		messages::create(
			messages::max_health(
				_id,
				_health.get()
			)
		)
	);
}

void
sanguis::server::world::object::exp_changed(
	server::player_id const _player_id,
	sanguis::entity_id const _entity_id,
	server::exp const _exp
)
{
	this->send_player_specific(
		_player_id,
		messages::create(
			messages::experience(
				_entity_id,
				// round EXP
				static_cast<
					sanguis::messages::types::exp
				>(
					_exp.get()
				)
			)
		)
	);
}

void
sanguis::server::world::object::level_changed(
	server::player_id const _player_id,
	sanguis::entity_id const _entity_id,
	server::level const _level
)
{
	this->send_player_specific(
		_player_id,
		messages::create(
			messages::level_up(
				_entity_id,
				_level.get()
			)
		)
	);
}

void
sanguis::server::world::object::pickup_chance(
	server::probability const _spawn_chance,
	server::center const &_center
)
{
	pickup_spawner_.spawn(
		_spawn_chance,
		_center
	);
}

void
sanguis::server::world::object::request_transfer(
	sanguis::world_id const _world_id,
	sanguis::entity_id const _entity_id,
	entities::insert_parameters const &_insert_parameters
)
{
	entity_map::iterator const it(
		entities_.find(
			_entity_id
		)
	);

	if(
		it == entities_.end()
	)
		throw sanguis::exception(
			FCPPT_TEXT("entity can't be transferred!")
		);

	entities::unique_ptr entity(
		entities_.release(
			it
		)
	);

	global_context_.transfer_entity(
		_world_id,
		move(
			entity
		),
		_insert_parameters
	);
}

void
sanguis::server::world::object::add_sight_range(
	server::player_id const _player_id,
	sanguis::entity_id const _target_id
)
{
	sight_ranges_[
		_player_id
	].add(
		_target_id
	);

	entity_map::iterator const it(
		entities_.find(
			_target_id
		)
	);

	if(
		it == entities_.end()
	)
		throw sanguis::exception(
			(
				fcppt::format(
					FCPPT_TEXT("Can't get entity %1% for sight update with player %2%!")
				)
				% _target_id
				% _player_id
			).str()
		);

	entities::base &entity(
		*it->second
	);

	if(
		entity.server_only()
	)
		return;
			
	this->send_player_specific(
		_player_id,
		it->second->add_message(
			_player_id
		)
	);
}

void
sanguis::server::world::object::remove_sight_range(
	server::player_id const _player_id,
	sanguis::entity_id const _target_id
)
{
	{
		sight_range_map::iterator const sight_it(
			sight_ranges_.find(
				_player_id
			)
		);

		FCPPT_ASSERT(
			sight_it != sight_ranges_.end()
		);

		sight_it->second.remove(
			_target_id
		);

		// if the player sees nothing here
		// it must have been deleted / moved
		// because the player always sees himself

		if(
			sight_it->second.empty()
		)
			sight_ranges_.erase(
				sight_it
			);
	}
	
	// if an entity has been removed
	// we have to tell the client that it is dead instead
	
	entity_map::const_iterator const it(
		entities_.find(
			_target_id
		)
	);

	FCPPT_ASSERT(
		it != entities_.end()
	);

	if(
		it->second->server_only()
	)
		return;

	this->send_player_specific(
		_player_id,
		it->second->dead()
		?
			messages::create(
				messages::die(
					_target_id
				)
			)
		:
			messages::create(
				messages::remove(
					_target_id
				)
			)
	);
}

void
sanguis::server::world::object::remove_player(
	server::player_id const _player_id
)
{
	global_context_.remove_player(
		_player_id
	);
}

sge::projectile::world &
sanguis::server::world::object::collision_world() const
{
	return *collision_world_;
}

sanguis::server::collision::global_groups const &
sanguis::server::world::object::global_collision_groups() const
{
	return collision_groups_;
}

sanguis::server::environment::load_context &
sanguis::server::world::object::load_context() const
{
	return load_context_;
}

void
sanguis::server::world::object::send_entity_specific(
	entity_id const _id,
	messages::auto_ptr _msg
)
{
	for(
		sight_range_map::const_iterator it(
			sight_ranges_.begin()
		);
		it != sight_ranges_.end();
		++it
	)
		if(
			it->second.contains(
				_id
			)
		)
			global_context_.send_to_player(
				it->first,
				_msg
			);
}

void
sanguis::server::world::object::send_player_specific(
	player_id const _player_id,
	messages::auto_ptr _msg
)
{
	global_context_.send_to_player(
		_player_id,
		_msg
	);
}

void
sanguis::server::world::object::update_entity(
	entity_map::iterator const _it,
	sanguis::time_delta const &_time,
	bool const _update_pos
)
{
	entities::base &entity(
		*_it->second
	);

	entity.update(
		_time
	);

	if(
		entity.dead()
	)
	{
		_it->second->remove();

		entities_.erase(
			_it
		);

		return;
	}

	if(
		entity.server_only()
		|| !_update_pos
	)
		return;

	FCPPT_TRY_DYNAMIC_CAST(
		entities::with_body const *,
		with_body,
		&entity
	)
		this->send_entity_specific(
			with_body->id(),
			message_convert::rotate(
				*with_body
			)
		);

	FCPPT_TRY_DYNAMIC_CAST(
		entities::with_velocity const *,
		movable,
		&entity
	)
	{
		this->send_entity_specific(
			movable->id(),
			message_convert::speed(
				*movable
			)
		);

		this->send_entity_specific(
			movable->id(),
			message_convert::move(
				*movable
			)
		);
	}

	FCPPT_TRY_DYNAMIC_CAST(
		entities::with_health const *,
		with_health,
		&entity
	)
		this->send_entity_specific(
			with_health->id(),
			message_convert::health(
				*with_health
			)
		);
}
