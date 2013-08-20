#include <sanguis/diff_timer.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/entity_id.hpp>
#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/timer.hpp>
#include <sanguis/world_id.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/creator/opening.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/top_result.hpp>
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
#include <sanguis/messages/remove_weapon.hpp>
#include <sanguis/messages/start_attacking.hpp>
#include <sanguis/messages/start_reloading.hpp>
#include <sanguis/messages/stop_attacking.hpp>
#include <sanguis/messages/stop_reloading.hpp>
#include <sanguis/messages/max_health.hpp>
#include <sanguis/messages/serialization/convert_string_vector.hpp>
#include <sanguis/messages/types/exp.hpp>
#include <sanguis/messages/types/size.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/log.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/source_world_id.hpp>
#include <sanguis/server/string.hpp>
#include <sanguis/server/collision/body_collision.hpp>
#include <sanguis/server/collision/global_groups.hpp>
#include <sanguis/server/collision/optional_result.hpp>
#include <sanguis/server/collision/with_world.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/is_type.hpp>
#include <sanguis/server/entities/optional_base_ref.hpp>
#include <sanguis/server/entities/player.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/global/source_world_pair.hpp>
#include <sanguis/server/message_convert/speed.hpp>
#include <sanguis/server/message_convert/rotate.hpp>
#include <sanguis/server/message_convert/move.hpp>
#include <sanguis/server/message_convert/health.hpp>
#include <sanguis/server/world/center_in_grid_pos.hpp>
#include <sanguis/server/world/context.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <sanguis/server/world/entity_map.hpp>
#include <sanguis/server/world/object.hpp>
#include <sanguis/server/world/parameters.hpp>
#include <sanguis/server/world/sight_range.hpp>
#include <sanguis/server/world/sight_range_map.hpp>
#include <sanguis/server/world/spawn_entity.hpp>
#include <sanguis/server/world/spawn_parameters.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <sge/projectile/time_increment.hpp>
#include <sge/projectile/world.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/try_dynamic_cast.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <functional>
#include <memory>
#include <fcppt/config/external_end.hpp>


sanguis::server::world::object::object(
	sanguis::server::world::parameters const &_parameters,
	sanguis::world_id const _id,
	sanguis::creator::top_result const &_generated_world,
	sanguis::server::world::difficulty const _difficulty
)
:
	sanguis::server::environment::object(),
	id_(
		_id
	),
	seed_(
		_generated_world.seed()
	),
	generator_name_(
		_generated_world.name()
	),
	grid_(
		_generated_world.grid()
	),
	openings_(
		_generated_world.openings()
	),
	global_context_(
		_parameters.context()
	),
	load_context_(
		_parameters.load_context()
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
			_parameters.diff_clock(),
			std::chrono::seconds(
				1
			)
		)
	),
	send_timer_(
		sanguis::timer::parameters(
			std::chrono::milliseconds(
				500
			)
		)
	),
	entities_(),
	server_entities_(),
	pickup_spawner_(
		_parameters.diff_clock(),
		_parameters.random_generator(),
		this->environment()
	)
{
	this->insert_spawns(
		_generated_world.spawns(),
		_parameters.diff_clock(),
		_parameters.random_generator(),
		_difficulty
	);
}

sanguis::server::world::object::~object()
{
}

void
sanguis::server::world::object::update()
{
	bool const update_pos(
		sge::timer::reset_when_expired(
			send_timer_
		)
	);

	sanguis::duration const duration(
		sge::timer::elapsed_and_reset<
			sanguis::duration
		>(
			projectile_timer_
		)
	);

	for(
		auto const entity
		:
		entities_
	)
		this->entity_collision(
			duration,
			*entity.second
		);

	collision_world_->update_continuous(
		sge::projectile::time_increment(
			std::chrono::duration_cast<
				sge::projectile::duration
			>(
				duration
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

	for(
		sanguis::server::world::object::entity_vector::iterator it(
			server_entities_.begin()
		);
		it != server_entities_.end();
	)
	{
		it->update();

		if(
			it->dead()
		)
		{
			// TODO: Simplify this!
			it->remove();

			it->destroy();

			it =
				server_entities_.erase(
					it
				);
		}
		else
			++it;
	}
}

sanguis::server::entities::optional_base_ref const
sanguis::server::world::object::insert(
	sanguis::server::entities::unique_ptr &&_entity,
	sanguis::server::entities::insert_parameters const &_insert_parameters
)
{
	return
		sanguis::server::entities::is_type<
			sanguis::server::entities::with_id
		>(
			*_entity
		)
		?
			this->insert_with_id(
				std::move(
					_entity
				),
				_insert_parameters
			)
		:
			this->insert_base(
				std::move(
					_entity
				),
				_insert_parameters
			)
		;
}
sanguis::server::environment::object &
sanguis::server::world::object::environment()
{
	return *this;
}

sanguis::creator::opening_container const &
sanguis::server::world::object::openings() const
{
	return openings_;
}

sanguis::server::entities::optional_base_ref const
sanguis::server::world::object::insert_with_id(
	sanguis::server::entities::unique_ptr &&_entity,
	sanguis::server::entities::insert_parameters const &_insert_parameters
)
{
	sanguis::server::entities::with_id_unique_ptr entity(
		&dynamic_cast<
			sanguis::server::entities::with_id &
		>(
			*_entity.release()
		)
	);

	sanguis::entity_id const id(
		entity->id()
	);

	typedef std::pair<
		sanguis::server::world::entity_map::iterator,
		bool
	> return_type;

	return_type const ret(
		entities_.insert(
			id,
			std::move(
				entity
			)
		)
	);

	FCPPT_ASSERT_ERROR(
		ret.second
	);

	sanguis::server::entities::base &result(
		*ret.first->second
	);

	if(
		!result.transfer(
			this->environment(),
			_insert_parameters,
			grid_
		)
	)
	{
		FCPPT_LOG_WARNING(
			sanguis::server::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Failed to spawn entity because its spawnpoint is obstructed")
		);

		entities_.erase(
			ret.first
		);

		return
			sanguis::server::entities::optional_base_ref();
	}

	FCPPT_TRY_DYNAMIC_CAST(
		sanguis::server::entities::player const *,
		player_ret,
		&result
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
					static_cast<
						sanguis::messages::types::size
					>(
						openings_.size()
					)
				)
			)
		);

	return
		sanguis::server::entities::optional_base_ref(
			result
		);
}

sanguis::server::entities::optional_base_ref const
sanguis::server::world::object::insert_base(
	sanguis::server::entities::unique_ptr &&_entity,
	sanguis::server::entities::insert_parameters const &_insert_parameters
)
{
	// These are only very simple entities that don't need special treatment
	fcppt::container::ptr::push_back_unique_ptr(
		server_entities_,
		std::move(
			_entity
		)
	);

	sanguis::server::entities::base &ref(
		server_entities_.back()
	);

	ref.transfer(
		this->environment(),
		_insert_parameters,
		grid_
	);

	return
		sanguis::server::entities::optional_base_ref(
			ref
		);
}

void
sanguis::server::world::object::weapon_changed(
	sanguis::entity_id const _id,
	sanguis::optional_primary_weapon_type const _wt
)
{
	this->send_entity_specific(
		_id,
		*sanguis::messages::create(
			sanguis::messages::change_weapon(
				_id,
				_wt
			)
		)
	);
}

void
sanguis::server::world::object::got_weapon(
	sanguis::server::player_id const _player_id,
	sanguis::entity_id const _entity_id,
	sanguis::weapon_description const &_description
)
{
	this->send_player_specific(
		_player_id,
		*sanguis::messages::create(
			sanguis::messages::give_weapon(
				_entity_id,
				_description.weapon_type(),
				sanguis::messages::serialization::convert_string_vector(
					_description.text()
				)
			)
		)
	);
}

void
sanguis::server::world::object::remove_weapon(
	sanguis::server::player_id const _player_id,
	sanguis::entity_id const _entity_id,
	sanguis::is_primary_weapon const _is_primary
)
{
	this->send_player_specific(
		_player_id,
		*sanguis::messages::create(
			sanguis::messages::remove_weapon(
				_entity_id,
				_is_primary
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
	sanguis::server::entities::enemies::difficulty const _difficulty,
	sanguis::server::center const &_center
)
{
	pickup_spawner_.spawn(
		_spawn_chance,
		_center,
		_difficulty
	);
}

void
sanguis::server::world::object::request_transfer(
	sanguis::entity_id const _entity_id
)
{
	sanguis::server::world::entity_map::iterator const it(
		entities_.find(
			_entity_id
		)
	);

	FCPPT_ASSERT_ERROR(
		it != entities_.end()
	);

	sanguis::server::entities::base &entity(
		*it->second
	);

	for(
		sanguis::creator::opening opening
		:
		openings_
	)
	{
		sanguis::server::global::source_world_pair const source_pair(
			sanguis::server::source_world_id(
				id_
			),
			opening
		);

		if(
			sanguis::server::world::center_in_grid_pos(
				entity.center(),
				opening.get()
			)
			&&
			global_context_.request_transfer(
				source_pair
			)

		)
		{
			entity.destroy();

			sanguis::server::entities::unique_ptr entity_ptr(
				entities_.release(
					it
				)
			);

			global_context_.transfer_entity(
				source_pair,
				std::move(
					entity_ptr
				)
			);

			return;
		}
	}
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

	FCPPT_ASSERT_ERROR(
		it != entities_.end()
	);

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

		// If the player sees nothing here, he must have been deleted
		// or moved, because the player always sees himself.
		if(
			sight_it->second.empty()
		)
			sight_ranges_.erase(
				sight_it
			);
	}

	// If an entity has been removed we have to tell the client that it is
	// dead instead

	sanguis::server::world::entity_map::const_iterator const it(
		entities_.find(
			_target_id
		)
	);

	FCPPT_ASSERT_ERROR(
		it != entities_.end()
	);

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
		!_update_pos
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

void
sanguis::server::world::object::entity_collision(
	sanguis::duration const &_duration,
	sanguis::server::entities::base &_entity
)
{
	FCPPT_TRY_DYNAMIC_CAST(
		sanguis::server::entities::with_body *,
		with_body,
		&_entity
	)
	{
		sanguis::server::collision::optional_result const result(
			sanguis::server::collision::with_world(
				*with_body,
				grid_,
				_duration
			)
		);

		if(
			result
		)
			with_body->world_collision(
				*result
			);
	}
}

void
sanguis::server::world::object::insert_spawns(
	sanguis::creator::spawn_container const &_spawns,
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::server::world::difficulty const _difficulty
)
{
	for(
		auto const &spawn : _spawns
	)
		this->insert(
			sanguis::server::world::spawn_entity(
				spawn,
				_diff_clock,
				_random_generator,
				this->load_context(),
				_difficulty
			),
			sanguis::server::world::spawn_parameters(
				spawn
			)
		);
}
