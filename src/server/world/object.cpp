#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/entity_id.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/timer.hpp>
#include <sanguis/world_id.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/creator/generator/result.hpp>
#include <sanguis/load/model/context.hpp>
#include <sanguis/load/model/collection.hpp>
#include <sanguis/load/model/object.hpp>
#include <sanguis/messages/base_fwd.hpp>
#include <sanguis/messages/change_weapon.hpp>
#include <sanguis/messages/change_world.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/die.hpp>
#include <sanguis/messages/experience.hpp>
#include <sanguis/messages/give_weapon.hpp>
#include <sanguis/messages/level_up.hpp>
#include <sanguis/messages/remove.hpp>
#include <sanguis/messages/start_attacking.hpp>
#include <sanguis/messages/start_reloading.hpp>
#include <sanguis/messages/stop_attacking.hpp>
#include <sanguis/messages/stop_reloading.hpp>
#include <sanguis/messages/max_health.hpp>
#include <sanguis/messages/types/enum.hpp>
#include <sanguis/messages/types/exp.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/console_fwd.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/string.hpp>
#include <sanguis/server/collision/body_collision.hpp>
#include <sanguis/server/collision/global_groups.hpp>
#include <sanguis/server/collision/group.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <sanguis/server/entities/player.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/message_convert/speed.hpp>
#include <sanguis/server/message_convert/rotate.hpp>
#include <sanguis/server/message_convert/move.hpp>
#include <sanguis/server/message_convert/health.hpp>
#include <sanguis/server/world/context.hpp>
#include <sanguis/server/world/create_static_body.hpp>
#include <sanguis/server/world/environment.hpp>
#include <sanguis/server/world/entity_map.hpp>
#include <sanguis/server/world/object.hpp>
#include <sanguis/server/world/sight_range.hpp>
#include <sanguis/server/world/sight_range_map.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <sge/projectile/time_increment.hpp>
#include <sge/projectile/world.hpp>
#include <sge/projectile/body/object.hpp>
#include <sge/projectile/group/sequence.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/try_dynamic_cast.hpp>
#include <fcppt/format.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/duration.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::server::world::object::object(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::world_id const _id,
	sanguis::server::world::context &_global_context,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::console &_console,
	sanguis::creator::generator::result const &_generated_world
)
:
	id_(
		_id
	),
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
			std::bind(
				&sanguis::server::collision::body_collision,
				std::placeholders::_1,
				std::placeholders::_2
			)
		)
	),
	sight_ranges_(),
	projectile_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			boost::chrono::seconds(
				1
			)
		)
	),
	send_timer_(
		sanguis::timer::parameters(
			boost::chrono::milliseconds(
				500
			)
		)
	),
	environment_(
		fcppt::make_unique_ptr<
			sanguis::server::world::environment
		>(
			*this
		)
	),
	entities_(),
	pickup_spawner_(
		_diff_clock,
		_random_generator,
		*environment_
	),
	wave_gen_(
		_diff_clock,
		_random_generator,
		_console
	),
	static_body_(
		sanguis::server::world::create_static_body(
			_generated_world.shapes()
		)
	),
	scoped_static_body_(
		*collision_world_,
		*static_body_,
		sge::projectile::group::sequence()
		/*
		fcppt::assign::make_container<
			sge::projectile::group::sequence
		>(
			fcppt::make_ref(
				collision_groups_.group(
					sanguis::server::collision::group::obstacle
				)
			)
		)*/
	)
{
}

sanguis::server::world::object::~object()
{
}

void
sanguis::server::world::object::update()
{
	wave_gen_.process(
		this->environment(),
		load_context_
	);

	// should we send position updates?
	bool const update_pos(
		sge::timer::reset_when_expired(
			send_timer_
		)
	);

	collision_world_->update_continuous(
		sge::projectile::time_increment(
			sge::timer::elapsed_and_reset<
				sge::projectile::duration
			>(
				projectile_timer_
			)
		)
	);

	for(
		sanguis::server::world::entity_map::iterator it(
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
			update_pos
		);
	}
}

void
sanguis::server::world::object::insert(
	sanguis::server::entities::unique_ptr &&_entity,
	sanguis::server::entities::insert_parameters const &_insert_parameters
)
{
	sanguis::entity_id const id(
		_entity->id()
	);

	typedef std::pair<
		sanguis::server::world::entity_map::iterator,
		bool
	> return_type;

	return_type const ret(
		entities_.insert(
			id,
			std::move(
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
		sanguis::server::entities::player const *,
		player_ret,
		ret.first->second
	)
		this->send_player_specific(
			player_ret->player_id(),
			*sanguis::messages::create(
				sanguis::messages::change_world(
					id_,
					seed_,
					sge::charconv::fcppt_string_to_utf8(
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
	sanguis::weapon_type const _wt
)
{
	this->send_entity_specific(
		_id,
		*sanguis::messages::create(
			sanguis::messages::change_weapon(
				_id,
				static_cast<
					sanguis::messages::types::enum_
				>(
					_wt
				)
			)
		)
	);
}

void
sanguis::server::world::object::got_weapon(
	sanguis::server::player_id const _player_id,
	sanguis::entity_id const _entity_id,
	sanguis::weapon_type const _wt
)
{
	this->send_player_specific(
		_player_id,
		*sanguis::messages::create(
			sanguis::messages::give_weapon(
				_entity_id,
				static_cast<
					sanguis::messages::types::enum_
				>(
					_wt
				)
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
			*sanguis::messages::create(
				sanguis::messages::start_attacking(
					_id
				)
			)
		:
			*sanguis::messages::create(
				sanguis::messages::stop_attacking(
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
			*sanguis::messages::create(
				sanguis::messages::start_reloading(
					_id
				)
			)
		:
			*sanguis::messages::create(
				sanguis::messages::stop_reloading(
					_id
				)
			)
	);
}

void
sanguis::server::world::object::max_health_changed(
	sanguis::entity_id const _id,
	sanguis::server::health const _health
)
{
	this->send_entity_specific(
		_id,
		*sanguis::messages::create(
			sanguis::messages::max_health(
				_id,
				_health.get()
			)
		)
	);
}

void
sanguis::server::world::object::exp_changed(
	sanguis::server::player_id const _player_id,
	sanguis::entity_id const _entity_id,
	sanguis::server::exp const _exp
)
{
	this->send_player_specific(
		_player_id,
		*sanguis::messages::create(
			sanguis::messages::experience(
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
	sanguis::server::player_id const _player_id,
	sanguis::entity_id const _entity_id,
	sanguis::server::level const _level
)
{
	this->send_player_specific(
		_player_id,
		*sanguis::messages::create(
			sanguis::messages::level_up(
				_entity_id,
				_level.get()
			)
		)
	);
}

void
sanguis::server::world::object::pickup_chance(
	sanguis::server::pickup_probability const _spawn_chance,
	sanguis::server::center const &_center
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
	sanguis::server::entities::insert_parameters const &_insert_parameters
)
{
	sanguis::server::world::entity_map::iterator const it(
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

	sanguis::server::entities::unique_ptr entity(
		entities_.release(
			it
		)
	);

	global_context_.transfer_entity(
		_world_id,
		std::move(
			entity
		),
		_insert_parameters
	);
}

void
sanguis::server::world::object::add_sight_range(
	sanguis::server::player_id const _player_id,
	sanguis::entity_id const _target_id
)
{
	sight_ranges_[
		_player_id
	].add(
		_target_id
	);

	sanguis::server::world::entity_map::iterator const it(
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

	sanguis::server::entities::base &entity(
		*it->second
	);

	if(
		entity.server_only()
	)
		return;

	this->send_player_specific(
		_player_id,
		*it->second->add_message(
			_player_id
		)
	);
}

void
sanguis::server::world::object::remove_sight_range(
	sanguis::server::player_id const _player_id,
	sanguis::entity_id const _target_id
)
{
	{
		sanguis::server::world::sight_range_map::iterator const sight_it(
			sight_ranges_.find(
				_player_id
			)
		);

		FCPPT_ASSERT_PRE(
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

	sanguis::server::world::entity_map::const_iterator const it(
		entities_.find(
			_target_id
		)
	);

	FCPPT_ASSERT_ERROR(
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
			*sanguis::messages::create(
				sanguis::messages::die(
					_target_id
				)
			)
		:
			*sanguis::messages::create(
				sanguis::messages::remove(
					_target_id
				)
			)
	);
}

void
sanguis::server::world::object::remove_player(
	sanguis::server::player_id const _player_id
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
	sanguis::entity_id const _id,
	sanguis::messages::base const &_msg
)
{
	for(
		auto sight_range : sight_ranges_
	)
		if(
			sight_range.second.contains(
				_id
			)
		)
			global_context_.send_to_player(
				sight_range.first,
				_msg
			);
}

void
sanguis::server::world::object::send_player_specific(
	sanguis::server::player_id const _player_id,
	sanguis::messages::base const &_msg
)
{
	global_context_.send_to_player(
		_player_id,
		_msg
	);
}

void
sanguis::server::world::object::update_entity(
	sanguis::server::world::entity_map::iterator const _it,
	bool const _update_pos
)
{
	sanguis::server::entities::base &entity(
		*_it->second
	);

	entity.update();

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
		sanguis::server::entities::with_body const *,
		with_body,
		&entity
	)
		this->send_entity_specific(
			with_body->id(),
			*sanguis::server::message_convert::rotate(
				*with_body
			)
		);

	FCPPT_TRY_DYNAMIC_CAST(
		sanguis::server::entities::with_velocity const *,
		movable,
		&entity
	)
	{
		this->send_entity_specific(
			movable->id(),
			*sanguis::server::message_convert::speed(
				*movable
			)
		);

		this->send_entity_specific(
			movable->id(),
			*sanguis::server::message_convert::move(
				*movable
			)
		);
	}

	FCPPT_TRY_DYNAMIC_CAST(
		sanguis::server::entities::with_health const *,
		with_health,
		&entity
	)
		this->send_entity_specific(
			with_health->id(),
			*sanguis::server::message_convert::health(
				*with_health
			)
		);
}
