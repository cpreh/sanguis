#include <sanguis/aura_type.hpp>
#include <sanguis/buff_type.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/entity_id.hpp>
#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/map_iteration.hpp>
#include <sanguis/magazine_remaining.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/sequence_iteration.hpp>
#include <sanguis/timer.hpp>
#include <sanguis/world_id.hpp>
#include <sanguis/world_name.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/collision/world/body_collision_callback.hpp>
#include <sanguis/collision/world/create.hpp>
#include <sanguis/collision/world/parameters.hpp>
#include <sanguis/collision/world/object.hpp>
#include <sanguis/creator/opening.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/top_result.hpp>
#include <sanguis/messages/convert/to_weapon_attribute_vector.hpp>
#include <sanguis/messages/server/add_aura.hpp>
#include <sanguis/messages/server/add_buff.hpp>
#include <sanguis/messages/server/base_fwd.hpp>
#include <sanguis/messages/server/change_weapon.hpp>
#include <sanguis/messages/server/change_world.hpp>
#include <sanguis/messages/server/create.hpp>
#include <sanguis/messages/server/die.hpp>
#include <sanguis/messages/server/experience.hpp>
#include <sanguis/messages/server/give_weapon.hpp>
#include <sanguis/messages/server/health.hpp>
#include <sanguis/messages/server/level_up.hpp>
#include <sanguis/messages/server/magazine_remaining.hpp>
#include <sanguis/messages/server/max_health.hpp>
#include <sanguis/messages/server/move.hpp>
#include <sanguis/messages/server/remove.hpp>
#include <sanguis/messages/server/remove_buff.hpp>
#include <sanguis/messages/server/remove_weapon.hpp>
#include <sanguis/messages/server/rotate.hpp>
#include <sanguis/messages/server/speed.hpp>
#include <sanguis/messages/server/weapon_status.hpp>
#include <sanguis/messages/types/exp.hpp>
#include <sanguis/messages/types/magazine_size.hpp>
#include <sanguis/messages/types/size.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/exp_for_level.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/log.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/source_world_id.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/string.hpp>
#include <sanguis/server/collision/body_collision.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/is_type.hpp>
#include <sanguis/server/entities/optional_base_ref.hpp>
#include <sanguis/server/entities/player.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/global/source_world_pair.hpp>
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
#include <sge/timer/elapsed_and_reset.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/truncation_check_cast.hpp>
#include <fcppt/try_dynamic_cast.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <functional>
#include <memory>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


sanguis::server::world::object::object(
	sanguis::server::world::parameters const &_parameters,
	sanguis::world_id const _id,
	sanguis::creator::top_result const &_generated_world,
	sanguis::server::world::difficulty const _difficulty,
	sanguis::world_name const &_name
)
:
	sanguis::server::environment::object(),
	id_(
		_id
	),
	seed_(
		_generated_world.seed()
	),
	difficulty_(
		_difficulty
	),
	name_(
		_name
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
		sanguis::collision::world::create(
			sanguis::collision::world::parameters(
				sanguis::collision::world::body_collision_callback(
					std::bind(
						&sanguis::server::collision::body_collision,
						std::placeholders::_1,
						std::placeholders::_2
					)
				),
				grid_.size()
			)
		)
	),
	sight_ranges_(),
	collision_timer_(
		sanguis::diff_timer::parameters(
			_parameters.diff_clock(),
			std::chrono::seconds(
				1
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
		_parameters.random_generator()
	);
}

sanguis::server::world::object::~object()
{
}

void
sanguis::server::world::object::update()
{
	sanguis::duration const duration(
		sge::timer::elapsed_and_reset<
			sanguis::duration
		>(
			collision_timer_
		)
	);

	// Don't process worlds that have no players in them
	if(
		sight_ranges_.empty()
	)
		return;

	for(
		auto const entity
		:
		entities_
	)
		entity.second->world_collision(
			grid_,
			duration
		);

	collision_world_->update(
		duration
	);

	auto const update_entity(
		[](
			sanguis::server::entities::base &_entity
		)
		{
			_entity.update();
		}
	);

	auto const entity_dead(
		[](
			sanguis::server::entities::base const &_entity
		)
		{
			return
				_entity.dead();
		}
	);

	auto const remove_entity(
		[](
			sanguis::server::entities::base &_entity
		)
		{
			_entity.remove();
		}
	);

	sanguis::map_iteration(
		entities_,
		update_entity,
		entity_dead,
		remove_entity
	);

	sanguis::sequence_iteration(
		server_entities_,
		update_entity,
		entity_dead,
		remove_entity
	);
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
	return
		*this;
}

sanguis::creator::opening_container const &
sanguis::server::world::object::openings() const
{
	return
		openings_;
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
			sanguis::messages::server::create(
				sanguis::messages::server::change_world(
					id_,
					seed_,
					sge::charconv::fcppt_string_to_utf8(
						generator_name_.get()
					),
					fcppt::cast::size<
						sanguis::messages::types::size
					>(
						openings_.size()
					),
					sge::charconv::fcppt_string_to_utf8(
						name_.get()
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
	server_entities_.push_back(
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
sanguis::server::world::object::add_aura(
	sanguis::entity_id const _id,
	sanguis::aura_type const _aura_type
)
{
	this->send_entity_specific(
		_id,
		sanguis::messages::server::create(
			sanguis::messages::server::add_aura(
				_id,
				_aura_type
			)
		)
	);
}

void
sanguis::server::world::object::add_buff(
	sanguis::entity_id const _id,
	sanguis::buff_type const _buff_type
)
{
	this->send_entity_specific(
		_id,
		sanguis::messages::server::create(
			sanguis::messages::server::add_buff(
				_id,
				_buff_type
			)
		)
	);
}

void
sanguis::server::world::object::remove_buff(
	sanguis::entity_id const _id,
	sanguis::buff_type const _buff_type
)
{
	this->send_entity_specific(
		_id,
		sanguis::messages::server::create(
			sanguis::messages::server::remove_buff(
				_id,
				_buff_type
			)
		)
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
		sanguis::messages::server::create(
			sanguis::messages::server::change_weapon(
				_id,
				_wt
			)
		)
	);
}

void
sanguis::server::world::object::got_weapon(
	sanguis::server::player_id const _player_id,
	sanguis::weapon_description const &_description
)
{
	this->send_player_specific(
		_player_id,
		sanguis::messages::server::create(
			sanguis::messages::server::give_weapon(
				_description.weapon_type(),
				fcppt::truncation_check_cast<
					sanguis::messages::types::magazine_size
				>(
					_description.magazine_size().get()
				),
				fcppt::truncation_check_cast<
					sanguis::messages::types::magazine_size
				>(
					_description.magazine_extra().get()
				),
				fcppt::truncation_check_cast<
					sanguis::messages::types::magazine_size
				>(
					_description.magazine_remaining().get()
				),
				sanguis::messages::convert::to_weapon_attribute_vector(
					_description.attributes()
				)
			)
		)
	);
}

void
sanguis::server::world::object::remove_weapon(
	sanguis::server::player_id const _player_id,
	sanguis::is_primary_weapon const _is_primary
)
{
	this->send_player_specific(
		_player_id,
		sanguis::messages::server::create(
			sanguis::messages::server::remove_weapon(
				_is_primary
			)
		)
	);
}

void
sanguis::server::world::object::magazine_remaining(
	sanguis::server::player_id const _player_id,
	sanguis::is_primary_weapon const _is_primary,
	sanguis::magazine_remaining const _magazine_remaining
)
{
	this->send_player_specific(
		_player_id,
		sanguis::messages::server::create(
			sanguis::messages::server::magazine_remaining(
				_is_primary,
				// TODO: Put this into a function!
				fcppt::truncation_check_cast<
					sanguis::messages::types::magazine_size
				>(
					_magazine_remaining.get()
				)
			)
		)
	);
}

void
sanguis::server::world::object::angle_changed(
	sanguis::entity_id const _entity_id,
	sanguis::server::angle const _angle
)
{
	this->send_entity_specific(
		_entity_id,
		sanguis::messages::server::create(
			sanguis::messages::server::rotate(
				_entity_id,
				_angle.get()
			)
		)
	);
}

void
sanguis::server::world::object::center_changed(
	sanguis::entity_id const _entity_id,
	sanguis::server::center const _center
)
{
	this->send_entity_specific(
		_entity_id,
		sanguis::messages::server::create(
			sanguis::messages::server::move(
				_entity_id,
				_center.get()
			)
		)
	);
}

void
sanguis::server::world::object::speed_changed(
	sanguis::entity_id const _entity_id,
	sanguis::server::speed const _speed
)
{
	this->send_entity_specific(
		_entity_id,
		sanguis::messages::server::create(
			sanguis::messages::server::speed(
				_entity_id,
				_speed.get()
			)
		)
	);
}

void
sanguis::server::world::object::weapon_status_changed(
	sanguis::entity_id const _id,
	sanguis::weapon_status const _weapon_status
)
{
	this->send_entity_specific(
		_id,
		sanguis::messages::server::create(
			sanguis::messages::server::weapon_status(
				_id,
				_weapon_status
			)
		)
	);
}

void
sanguis::server::world::object::health_changed(
	sanguis::entity_id const _id,
	sanguis::server::health const _health
)
{
	this->send_entity_specific(
		_id,
		sanguis::messages::server::create(
			sanguis::messages::server::health(
				_id,
				_health.get()
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
		sanguis::messages::server::create(
			sanguis::messages::server::max_health(
				_id,
				_health.get()
			)
		)
	);
}

void
sanguis::server::world::object::exp_changed(
	sanguis::server::player_id const _player_id,
	sanguis::server::exp const _exp
)
{
	this->send_player_specific(
		_player_id,
		sanguis::messages::server::create(
			sanguis::messages::server::experience(
				fcppt::cast::to_unsigned(
					fcppt::cast::float_to_int<
						std::make_signed<
							sanguis::messages::types::exp
						>::type
					>(
						_exp.get()
					)
				)
			)
		)
	);
}

void
sanguis::server::world::object::level_changed(
	sanguis::server::player_id const _player_id,
	sanguis::server::level const _level
)
{
	this->send_player_specific(
		_player_id,
		sanguis::messages::server::create(
			sanguis::messages::server::level_up(
				_level.get(),
				// TODO: Refactor this into a function!
				fcppt::cast::to_unsigned(
					fcppt::cast::float_to_int<
						std::make_signed<
							sanguis::messages::types::exp
						>::type
					>(
						sanguis::server::exp_for_level(
							_level
							+
							sanguis::server::level(
								1u
							)
						).get()
					)
				)
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
			// TODO: Can we do this in a different way?
			entity.reset_body();

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

sanguis::server::world::difficulty const
sanguis::server::world::object::difficulty() const
{
	return
		difficulty_;
}

sanguis::collision::world::object &
sanguis::server::world::object::collision_world() const
{
	return
		*collision_world_;
}

sanguis::creator::grid const &
sanguis::server::world::object::grid() const
{
	return
		grid_;
}

sanguis::server::environment::load_context &
sanguis::server::world::object::load_context() const
{
	return
		load_context_;
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

	if(
		it->second->dead()
	)
		this->send_player_specific(
			_player_id,
			sanguis::messages::server::create(
				sanguis::messages::server::die(
					_target_id
				)
			)
		);
	else
		this->send_player_specific(
			_player_id,
			sanguis::messages::server::create(
				sanguis::messages::server::remove(
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

void
sanguis::server::world::object::send_entity_specific(
	sanguis::entity_id const _id,
	sanguis::messages::server::base const &_msg
)
{
	for(
		auto sight_range
		:
		sight_ranges_
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
	sanguis::messages::server::base const &_msg
)
{
	global_context_.send_to_player(
		_player_id,
		_msg
	);
}

void
sanguis::server::world::object::insert_spawns(
	sanguis::creator::spawn_container const &_spawns,
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator
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
				difficulty_
			),
			sanguis::server::world::spawn_parameters(
				spawn
			)
		);
}
