#include <sanguis/aura_type.hpp>
#include <sanguis/buff_type.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/entity_id.hpp>
#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/magazine_remaining.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/timer.hpp>
#include <sanguis/world_id.hpp>
#include <sanguis/world_name.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/collision/world/body_collision_callback.hpp>
#include <sanguis/collision/world/create.hpp>
#include <sanguis/collision/world/parameters.hpp>
#include <sanguis/collision/world/object.hpp>
#include <sanguis/creator/destructible.hpp>
#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/opening.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/spawn.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/top_result.hpp>
#include <sanguis/messages/convert/to_magazine_size.hpp>
#include <sanguis/messages/convert/to_weapon_attribute_vector.hpp>
#include <sanguis/messages/roles/angle.hpp>
#include <sanguis/messages/roles/aura_type.hpp>
#include <sanguis/messages/roles/buff_type.hpp>
#include <sanguis/messages/roles/center.hpp>
#include <sanguis/messages/roles/entity_id.hpp>
#include <sanguis/messages/roles/experience.hpp>
#include <sanguis/messages/roles/exp_for_next_level.hpp>
#include <sanguis/messages/roles/generator_name.hpp>
#include <sanguis/messages/roles/health.hpp>
#include <sanguis/messages/roles/is_primary_weapon.hpp>
#include <sanguis/messages/roles/level.hpp>
#include <sanguis/messages/roles/magazine_base_size.hpp>
#include <sanguis/messages/roles/magazine_extra_size.hpp>
#include <sanguis/messages/roles/magazine_remaining.hpp>
#include <sanguis/messages/roles/max_health.hpp>
#include <sanguis/messages/roles/opening_count.hpp>
#include <sanguis/messages/roles/primary_weapon.hpp>
#include <sanguis/messages/roles/reload_time.hpp>
#include <sanguis/messages/roles/seed.hpp>
#include <sanguis/messages/roles/speed.hpp>
#include <sanguis/messages/roles/weapon_attribute_container.hpp>
#include <sanguis/messages/roles/weapon_status.hpp>
#include <sanguis/messages/roles/weapon_type.hpp>
#include <sanguis/messages/roles/world_id.hpp>
#include <sanguis/messages/roles/world_name.hpp>
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
#include <sanguis/messages/server/reload.hpp>
#include <sanguis/messages/server/remove.hpp>
#include <sanguis/messages/server/remove_buff.hpp>
#include <sanguis/messages/server/remove_weapon.hpp>
#include <sanguis/messages/server/rotate.hpp>
#include <sanguis/messages/server/speed.hpp>
#include <sanguis/messages/server/weapon_status.hpp>
#include <sanguis/messages/types/size.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/exp_for_level.hpp>
#include <sanguis/server/exp_to_net.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/log.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/source_world_id.hpp>
#include <sanguis/server/speed.hpp>
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
#include <sanguis/server/world/generate_destructibles.hpp>
#include <sanguis/server/world/generate_spawns.hpp>
#include <sanguis/server/world/insert_pair.hpp>
#include <sanguis/server/world/insert_pair_container.hpp>
#include <sanguis/server/world/object.hpp>
#include <sanguis/server/world/parameters.hpp>
#include <sanguis/server/world/sight_range.hpp>
#include <sanguis/server/world/sight_range_map.hpp>
#include <sanguis/server/world/update_entity.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/try_dynamic_cast.hpp>
#include <fcppt/algorithm/map_iteration_second.hpp>
#include <fcppt/algorithm/sequence_iteration.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <memory>
#include <utility>
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
	entities_(),
	server_entities_(),
	pickup_spawner_(
		_parameters.random_generator(),
		this->environment()
	)
{
	this->insert_spawns(
		_generated_world.spawns(),
		_parameters.random_generator()
	);

	this->insert_destructibles(
		_generated_world.destructibles(),
		_parameters.random_generator()
	);
}

sanguis::server::world::object::~object()
{
}

void
sanguis::server::world::object::update(
	sanguis::duration const &_elapsed_time
)
{
	// Don't process worlds that have no players in them
	if(
		sight_ranges_.empty()
	)
		return;

	for(
		auto &cur_entity
		:
		entities_
	)
		cur_entity.second->world_collision(
			grid_,
			_elapsed_time
		);

	collision_world_->update(
		_elapsed_time
	);

	sanguis::server::world::update_entity const update_entity{
		_elapsed_time
	};

	fcppt::algorithm::map_iteration_second(
		entities_,
		update_entity
	);

	fcppt::algorithm::sequence_iteration(
		server_entities_,
		update_entity
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

sanguis::server::entities::optional_base_ref const
sanguis::server::world::object::insert(
	sanguis::server::world::insert_pair &&_pair
)
{
	return
		this->insert(
			std::move(
				_pair.entity()
			),
			_pair.insert_parameters()
		);
}

void
sanguis::server::world::object::insert(
	sanguis::server::world::insert_pair_container &&_pairs
)
{
	for(
		sanguis::server::world::insert_pair &element
		:
		_pairs
	)
		this->insert(
			std::move(
				element
			)
		);
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

sanguis::world_id const
sanguis::server::world::object::world_id() const
{
	return
		id_;
}

sanguis::server::entities::optional_base_ref const
sanguis::server::world::object::insert_with_id(
	sanguis::server::entities::unique_ptr &&_entity,
	sanguis::server::entities::insert_parameters const &_insert_parameters
)
{
	sanguis::server::entities::with_id_unique_ptr cur_entity(
		&dynamic_cast<
			sanguis::server::entities::with_id &
		>(
			*_entity.release()
		)
	);

	sanguis::entity_id const id(
		cur_entity->id()
	);

	typedef std::pair<
		sanguis::server::world::entity_map::iterator,
		bool
	> return_type;

	return_type const ret(
		entities_.insert(
			id,
			std::move(
				cur_entity
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
					sanguis::messages::roles::world_id{} =
						id_,
					sanguis::messages::roles::seed{} =
						seed_,
					sanguis::messages::roles::generator_name{} =
						sge::charconv::fcppt_string_to_utf8(
							generator_name_.get()
						),
					sanguis::messages::roles::opening_count{} =
						fcppt::cast::size<
							sanguis::messages::types::size
						>(
							openings_.size()
						),
					sanguis::messages::roles::world_name{} =
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
				sanguis::messages::roles::entity_id{} =
					_id,
				sanguis::messages::roles::aura_type{} =
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
				sanguis::messages::roles::entity_id{} =
					_id,
				sanguis::messages::roles::buff_type{} =
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
				sanguis::messages::roles::entity_id{} =
					_id,
				sanguis::messages::roles::buff_type{} =
					_buff_type
			)
		)
	);
}

void
sanguis::server::world::object::weapon_changed(
	sanguis::entity_id const _id,
	sanguis::optional_primary_weapon_type const _weapon_type
)
{
	this->send_entity_specific(
		_id,
		sanguis::messages::server::create(
			sanguis::messages::server::change_weapon(
				sanguis::messages::roles::entity_id{} =
					_id,
				sanguis::messages::roles::primary_weapon{} =
					_weapon_type
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
				sanguis::messages::roles::weapon_type{} =
					_description.weapon_type(),
				sanguis::messages::roles::magazine_base_size{} =
					sanguis::messages::convert::to_magazine_size(
						_description.magazine_size().get()
					),
				sanguis::messages::roles::magazine_extra_size{} =
					sanguis::messages::convert::to_magazine_size(
						_description.magazine_extra().get()
					),
				sanguis::messages::roles::magazine_remaining{} =
					sanguis::messages::convert::to_magazine_size(
						_description.magazine_remaining().get()
					),
				sanguis::messages::roles::reload_time{} =
					_description.reload_time().get(),
				sanguis::messages::roles::weapon_attribute_container{} =
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
				sanguis::messages::roles::is_primary_weapon{} =
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
				sanguis::messages::roles::is_primary_weapon{} =
					_is_primary,
				sanguis::messages::roles::magazine_remaining{} =
					sanguis::messages::convert::to_magazine_size(
						_magazine_remaining.get()
					)
			)
		)
	);
}

void
sanguis::server::world::object::reload_time(
	sanguis::server::player_id const _player_id,
	sanguis::is_primary_weapon const _is_primary,
	sanguis::duration const _reload_time
)
{
	this->send_player_specific(
		_player_id,
		sanguis::messages::server::create(
			sanguis::messages::server::reload(
				sanguis::messages::roles::is_primary_weapon{} =
					_is_primary,
				sanguis::messages::roles::reload_time{} =
					_reload_time
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
				sanguis::messages::roles::entity_id{} =
					_entity_id,
				sanguis::messages::roles::angle{} =
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
				sanguis::messages::roles::entity_id{} =
					_entity_id,
				sanguis::messages::roles::center{} =
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
				sanguis::messages::roles::entity_id{} =
					_entity_id,
				sanguis::messages::roles::speed{} =
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
				sanguis::messages::roles::entity_id{} =
					_id,
				sanguis::messages::roles::weapon_status{} =
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
				sanguis::messages::roles::entity_id{} =
					_id,
				sanguis::messages::roles::health{} =
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
				sanguis::messages::roles::entity_id{} =
					_id,
				sanguis::messages::roles::max_health{} =
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
				sanguis::messages::roles::experience{} =
					sanguis::server::exp_to_net(
						_exp
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
				sanguis::messages::roles::level{} =
					_level.get(),
				sanguis::messages::roles::exp_for_next_level{} =
					sanguis::server::exp_to_net(
						sanguis::server::exp_for_level(
							_level
							+
							sanguis::server::level(
								1u
							)
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
		it
		!=
		entities_.end()
	);

	sanguis::server::entities::base &cur_entity(
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
				cur_entity.center(),
				opening.get()
			)
			&&
			global_context_.request_transfer(
				source_pair
			)

		)
		{
			// TODO: Can we do this in a different way?
			cur_entity.reset_body();

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

	this->send_player_specific(
		_player_id,
		*this->entity(
			_target_id
		).add_message(
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
			sight_it
			!=
			sight_ranges_.end()
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

	if(
		this->entity(
			_target_id
		).dead()
	)
		this->send_player_specific(
			_player_id,
			sanguis::messages::server::create(
				sanguis::messages::server::die(
					sanguis::messages::roles::entity_id{} =
						_target_id
				)
			)
		);
	else
		this->send_player_specific(
			_player_id,
			sanguis::messages::server::create(
				sanguis::messages::server::remove(
					sanguis::messages::roles::entity_id{} =
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
	sanguis::random_generator &_random_generator
)
{
	for(
		sanguis::creator::spawn const &spawn
		:
		_spawns
	)
		this->insert(
			sanguis::server::world::generate_spawns(
				spawn,
				_random_generator,
				this->load_context(),
				difficulty_
			)
		);
}

void
sanguis::server::world::object::insert_destructibles(
	sanguis::creator::destructible_container const &_destructibles,
	sanguis::random_generator &_random_generator
)
{
	for(
		sanguis::creator::destructible const &destructible
		:
		_destructibles
	)
		this->insert(
			sanguis::server::world::generate_destructibles(
				_random_generator,
				destructible,
				this->load_context(),
				difficulty_
			)
		);
}

sanguis::server::entities::with_id &
sanguis::server::world::object::entity(
	sanguis::entity_id const _id
)
{
	sanguis::server::world::entity_map::iterator const it(
		entities_.find(
			_id
		)
	);

	FCPPT_ASSERT_ERROR(
		it
		!=
		entities_.end()
	);

	return
		*it->second;
}
