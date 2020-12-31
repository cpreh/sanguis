#include <sanguis/aura_type.hpp>
#include <sanguis/buff_type.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/entity_id.hpp>
#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/magazine_remaining.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/timer.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/world_id.hpp>
#include <sanguis/world_name.hpp>
#include <sanguis/collision/log.hpp>
#include <sanguis/collision/world/create.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/collision/world/object.hpp>
#include <sanguis/collision/world/parameters.hpp>
#include <sanguis/collision/world/update_result.hpp>
#include <sanguis/creator/destructible.hpp>
#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/opening.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/opening_type.hpp>
#include <sanguis/creator/spawn.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/spawn_type.hpp>
#include <sanguis/creator/top_result.hpp>
#include <sanguis/messages/convert/to_magazine_size.hpp>
#include <sanguis/messages/convert/to_weapon_attribute_vector.hpp>
#include <sanguis/messages/roles/angle.hpp>
#include <sanguis/messages/roles/aura_type.hpp>
#include <sanguis/messages/roles/buff_type.hpp>
#include <sanguis/messages/roles/center.hpp>
#include <sanguis/messages/roles/entity_id.hpp>
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
#include <sanguis/messages/roles/spawn_boss.hpp>
#include <sanguis/messages/roles/speed.hpp>
#include <sanguis/messages/roles/weapon_attribute_container.hpp>
#include <sanguis/messages/roles/weapon_status.hpp>
#include <sanguis/messages/roles/weapon_type.hpp>
#include <sanguis/messages/roles/world_id.hpp>
#include <sanguis/messages/roles/world_name.hpp>
#include <sanguis/messages/server/add_aura.hpp>
#include <sanguis/messages/server/add_buff.hpp>
#include <sanguis/messages/server/base.hpp>
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
#include <sanguis/messages/types/opening_count_array.hpp>
#include <sanguis/messages/types/size.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/exp_for_level.hpp>
#include <sanguis/server/exp_to_net.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/log_location.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/source_world_id.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/collision/body_collision.hpp>
#include <sanguis/server/collision/body_enter.hpp>
#include <sanguis/server/collision/body_exit.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/doodad.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/optional_base_ref.hpp>
#include <sanguis/server/entities/optional_transfer_result.hpp>
#include <sanguis/server/entities/remove_from_world_result.hpp>
#include <sanguis/server/entities/simple.hpp>
#include <sanguis/server/entities/simple_unique_ptr.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/global/source_world_pair.hpp>
#include <sanguis/server/weapons/common_parameters_fwd.hpp>
#include <sanguis/server/world/center_in_grid_pos.hpp>
#include <sanguis/server/world/context.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <sanguis/server/world/generate_destructibles.hpp>
#include <sanguis/server/world/generate_single_spawns.hpp>
#include <sanguis/server/world/grid_pos_to_center.hpp>
#include <sanguis/server/world/insert_simple_pair.hpp>
#include <sanguis/server/world/insert_with_id_pair.hpp>
#include <sanguis/server/world/insert_with_id_pair_container.hpp>
#include <sanguis/server/world/make_portal_blocker.hpp>
#include <sanguis/server/world/make_spawner.hpp>
#include <sanguis/server/world/object.hpp>
#include <sanguis/server/world/parameters.hpp>
#include <sanguis/server/world/sight_range.hpp>
#include <sanguis/server/world/sight_range_map.hpp>
#include <sanguis/server/world/update_entity.hpp>
#include <alda/message/init_record.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <fcppt/copy.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/map_iteration_second.hpp>
#include <fcppt/algorithm/sequence_iteration.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/container/find_opt_iterator.hpp>
#include <fcppt/container/make.hpp>
#include <fcppt/enum/array_init.hpp>
#include <fcppt/enum/make_range.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/parameters_no_function.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/preprocessor/disable_gnu_gcc_warning.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::server::world::object::object(
	sanguis::server::world::parameters const &_parameters,
	sanguis::world_id const _id,
	sanguis::creator::top_result const &_generated_world,
	sanguis::server::world::difficulty const _difficulty,
	sanguis::world_name &&_name
)
:
	sanguis::server::environment::object(),
	log_{
		fcppt::make_ref(
			_parameters.log_context()
		),
		sanguis::server::log_location(),
		// TODO(philipp): Add world name?
		fcppt::log::parameters_no_function(
			fcppt::log::name{
				FCPPT_TEXT("world")
			}
		)
	},
	info_(
		_id,
		std::move(
			_name
		),
		_generated_world.seed(),
		fcppt::copy(
			_generated_world.name()
		),
		_generated_world.spawn_boss(),
		fcppt::copy(
			_generated_world.openings()
		)
	),
	difficulty_(
		_difficulty
	),
	grid_(
		_generated_world.grid()
	),
	global_context_(
		_parameters.context()
	),
	load_context_(
		_parameters.load_context()
	),
	collision_log_{
		// TODO(philipp): Add world name?
		fcppt::make_ref(
			_parameters.log_context()
		)
	},
	collision_world_(
		sanguis::collision::world::create(
			sanguis::collision::world::parameters(
				fcppt::make_cref(
					grid_
				)
			)
		)
	),
	sight_ranges_(),
	entities_(),
	server_entities_(),
	portal_blockers_(),
	portal_block_count_{
		0U
	},
	pickup_spawner_(
		fcppt::make_ref(
			_parameters.random_generator()
		),
		_parameters.weapon_parameters(),
		fcppt::make_ref(
			this->environment()
		)
	)
{
	this->insert_spawns(
		_generated_world.spawns(),
		fcppt::make_ref(
			_parameters.random_generator()
		),
		_parameters.weapon_parameters()
	);

	this->insert_destructibles(
		_generated_world.destructibles(),
		_parameters.random_generator()
	);
}

FCPPT_PP_POP_WARNING

sanguis::server::world::object::~object()
= default;

void
sanguis::server::world::object::update(
	sanguis::duration const &_elapsed_time
)
{
	// Don't process worlds that have no players in them
	if(
		sight_ranges_.empty()
	)
	{
		return;
	}

	sanguis::collision::world::update_result const collision_result(
		collision_world_->update(
			_elapsed_time
		)
	);

	sanguis::server::collision::body_collision(
		collision_result.body_collision()
	);

	sanguis::server::collision::body_enter(
		collision_result.body_enter()
	);

	sanguis::server::collision::body_exit(
		collision_result.body_exit()
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

	fcppt::algorithm::sequence_iteration(
		portal_blockers_,
		update_entity
	);
}

sanguis::server::entities::optional_base_ref
sanguis::server::world::object::insert(
	sanguis::server::entities::simple_unique_ptr &&_entity,
	sanguis::server::entities::insert_parameters const &_insert_parameters
)
{
	return
		fcppt::optional::map(
			this->insert_base(
				server_entities_,
				std::move(
					_entity
				),
				_insert_parameters
			),
			[](
				fcppt::reference<
					sanguis::server::entities::simple
				> const _simple
			)
			{
				return
					fcppt::reference_to_base<
						sanguis::server::entities::base
					>(
						_simple
					);
			}
		);
}

sanguis::server::entities::optional_base_ref
sanguis::server::world::object::insert(
	sanguis::server::entities::with_id_unique_ptr &&_entity,
	sanguis::server::entities::insert_parameters const &_insert_parameters
)
{
	return
		fcppt::optional::maybe(
			_entity->transfer(
				fcppt::make_ref(
					this->environment()
				),
				_insert_parameters,
				fcppt::make_cref(
					this->grid_
				)
			),
			[
				this
			]
			{
				FCPPT_LOG_WARNING(
					log_,
					fcppt::log::out
						<< FCPPT_TEXT("Failed to spawn entity because its spawnpoint is obstructed")
				)

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GNU_GCC_WARNING(-Wmaybe-uninitialized)
				return
					sanguis::server::entities::optional_base_ref();
FCPPT_PP_POP_WARNING
			},
			[
				this,
				&_entity
			](
				sanguis::server::entities::transfer_result const &_transfer_result
			)
			{
				sanguis::entity_id const id(
					_entity->id()
				);

				using
				return_type
				=
				std::pair<
					entity_map::iterator,
					bool
				>;

				return_type const ret(
					entities_.insert(
						std::make_pair(
							id,
							std::move(
								_entity
							)
						)
					)
				);

				FCPPT_ASSERT_ERROR(
					ret.second
				);

				sanguis::server::entities::with_id &result(
					*ret.first->second
				);

				result.transfer_to_world();

				sanguis::server::collision::body_enter(
					_transfer_result.body_enter()
				);

				return
					sanguis::server::entities::optional_base_ref(
						fcppt::reference_to_base<
							sanguis::server::entities::base
						>(
							fcppt::make_ref(
								result
							)
						)
					);
			}
		);
}

sanguis::server::entities::optional_base_ref
sanguis::server::world::object::insert(
	sanguis::server::world::insert_with_id_pair &&_pair
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
	sanguis::server::world::insert_with_id_pair_container &&_pairs
)
{
	for(
		sanguis::server::world::insert_with_id_pair &element
		:
		_pairs
	)
		this->insert(
			std::move(
				element
			)
		);
}

sanguis::server::entities::optional_base_ref
sanguis::server::world::object::insert(
	sanguis::server::world::insert_simple_pair &&_pair
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

sanguis::server::environment::object &
sanguis::server::world::object::environment()
{
	return
		*this;
}

sanguis::creator::opening_container_array const &
sanguis::server::world::object::openings() const
{
	return
		info_.openings();
}

sanguis::world_id
sanguis::server::world::object::world_id() const
{
	return
		info_.world_id();
}

void
sanguis::server::world::object::player_insertion(
	sanguis::server::player_id const _player_id
)
{
	this->send_player_specific(
		_player_id,
		sanguis::messages::server::create(
			alda::message::init_record<
				sanguis::messages::server::change_world
			>(
				sanguis::messages::roles::world_id{} =
					this->world_id(),
				sanguis::messages::roles::seed{} =
					info_.seed(),
				sanguis::messages::roles::generator_name{} =
					sge::charconv::fcppt_string_to_utf8(
						info_.generator_name().get()
					),
				sanguis::messages::roles::opening_count{} =
					fcppt::enum_::array_init<
						sanguis::messages::types::opening_count_array
					>(
						[
							this
						](
							sanguis::creator::opening_type const _opening_type
						)
						{
							return
								fcppt::cast::size<
									sanguis::messages::types::size
								>(
									info_.openings()[
										_opening_type
									].size()
								);
						}
					),
				sanguis::messages::roles::world_name{} =
					sge::charconv::fcppt_string_to_utf8(
						info_.world_name().get()
					),
				sanguis::messages::roles::spawn_boss{} =
					info_.spawn_boss().get()
			)
		)
	);
}

template<
	typename Entity
>
fcppt::optional::reference<
	Entity
>
sanguis::server::world::object::insert_base(
	std::vector<
		fcppt::unique_ptr<
			Entity
		>
	> &_container,
	fcppt::unique_ptr<
		Entity
	> &&_entity,
	sanguis::server::entities::insert_parameters const &_insert_parameters
)
{
	// These are only very simple entities that don't need special treatment
	return
		fcppt::optional::map(
			_entity->transfer(
				fcppt::make_ref(
					this->environment()
				),
				_insert_parameters,
				fcppt::make_cref(
					this->grid_
				)
			),
			[
				&_container,
				&_entity
			](
				sanguis::server::entities::transfer_result const &_transfer_result
			)
			{
				_container.push_back(
					std::move(
						_entity
					)
				);

				sanguis::server::collision::body_enter(
					_transfer_result.body_enter()
				);

				return
					fcppt::make_ref(
						*_container.back()
					);
			}
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
			alda::message::init_record<
				sanguis::messages::server::add_aura
			>(
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
			alda::message::init_record<
				sanguis::messages::server::add_buff
			>(
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
			alda::message::init_record<
				sanguis::messages::server::remove_buff
			>(
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
			alda::message::init_record<
				sanguis::messages::server::change_weapon
			>(
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
			alda::message::init_record<
				sanguis::messages::server::give_weapon
			>(
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
			sanguis::messages::server::remove_weapon{
				_is_primary
			}
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
			alda::message::init_record<
				sanguis::messages::server::magazine_remaining
			>(
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
			alda::message::init_record<
				sanguis::messages::server::reload
			>(
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
			alda::message::init_record<
				sanguis::messages::server::rotate
			>(
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
			alda::message::init_record<
				sanguis::messages::server::move
			>(
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
			alda::message::init_record<
				sanguis::messages::server::speed
			>(
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
			alda::message::init_record<
				sanguis::messages::server::weapon_status
			>(
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
			alda::message::init_record<
				sanguis::messages::server::health
			>(
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
			alda::message::init_record<
				sanguis::messages::server::max_health
			>(
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
			sanguis::messages::server::experience{
				sanguis::server::exp_to_net(
					_exp
				)
			}
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
			alda::message::init_record<
				sanguis::messages::server::level_up
			>(
				sanguis::messages::roles::level{} =
					_level.get(),
				sanguis::messages::roles::exp_for_next_level{} =
					sanguis::server::exp_to_net(
						sanguis::server::exp_for_level(
							_level
							+
							sanguis::server::level(
								1U
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
	sanguis::server::center const _center
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
	entity_map::iterator const it(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			fcppt::container::find_opt_iterator(
				entities_,
				_entity_id
			)
		)
	);

	sanguis::server::entities::base &cur_entity(
		*it->second
	);

	for(
		auto const opening_type
		:
		fcppt::enum_::make_range<
			sanguis::creator::opening_type
		>()
	)
	{
		if(
			opening_type
			==
			sanguis::creator::opening_type::exit
			&&
			portal_block_count_
			>
			0U
		)
		{
			continue;
		}

		for(
			sanguis::creator::opening const &opening
			:
			info_.openings()[
				opening_type
			]
		)
		{
			sanguis::server::global::source_world_pair const source_pair{
				sanguis::server::source_world_id(
					this->world_id()
				),
				opening
			};

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
				sanguis::server::collision::body_exit(
					cur_entity.remove_from_world().body_exit()
				);

				sanguis::server::entities::with_id_unique_ptr entity_ptr(
					fcppt::unique_ptr_to_base<
						sanguis::server::entities::with_id
					>(
						std::move(
							it->second
						)
					)
				);

				entities_.erase(
					it
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
}

void
sanguis::server::world::object::add_portal_blocker()
{
	if(
		portal_block_count_
		==
		0U
	)
	{
		for(
			auto const &portal
			:
			info_.openings()[
				sanguis::creator::opening_type::exit
			]
		)
		{
			this->insert_base(
				portal_blockers_,
				sanguis::server::world::make_portal_blocker(
					this->load_context()
				),
				sanguis::server::entities::insert_parameters_center(
					sanguis::server::world::grid_pos_to_center(
						portal.get()
					)
				)
			);
		}
	}

	++portal_block_count_;
}

void
sanguis::server::world::object::remove_portal_blocker()
{
	FCPPT_ASSERT_ERROR(
		portal_block_count_
		>
		0U
	);

	--portal_block_count_;

	if(
		portal_block_count_
		==
		0U
	)
	{
		for(
			auto const &portal_blocker
			:
			portal_blockers_
		)
		{
			portal_blocker->kill();
		}
	}
}

sanguis::server::world::difficulty
sanguis::server::world::object::difficulty() const
{
	return
		difficulty_;
}

sanguis::collision::log const &
sanguis::server::world::object::collision_log() const
{
	return
		collision_log_;
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
	sanguis::server::entities::with_id const &_target,
	sanguis::collision::world::created const _created
)
{
	sight_ranges_[
		_player_id
	].add(
		_target.id()
	);

	this->send_player_specific(
		_player_id,
		*_target.add_message(
			_player_id,
			_created
		)
	);
}

void
sanguis::server::world::object::remove_sight_range(
	sanguis::server::player_id const _player_id,
	sanguis::server::entities::with_id const &_target
)
{
	{
		sanguis::server::world::sight_range_map::iterator const sight_it(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				fcppt::container::find_opt_iterator(
					sight_ranges_,
					_player_id
				)
			)
		);

		sight_it->second.remove(
			_target.id()
		);

		// If the player sees nothing here, he must have been deleted
		// or moved, because the player always sees himself.
		if(
			sight_it->second.empty()
		)
		{
			sight_ranges_.erase(
				sight_it
			);
		}
	}

	if(
		_target.dead()
	)
	{
		this->send_player_specific(
			_player_id,
			sanguis::messages::server::create(
				alda::message::init_record<
					sanguis::messages::server::die
				>(
					sanguis::messages::roles::entity_id{} =
						_target.id()
				)
			)
		);
	}
	else
	{
		this->send_player_specific(
			_player_id,
			sanguis::messages::server::create(
				alda::message::init_record<
					sanguis::messages::server::remove
				>(
					sanguis::messages::roles::entity_id{} =
						_target.id()
				)
			)
		);
	}
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
		sanguis::server::world::sight_range_map::value_type const &sight_range
		:
		sight_ranges_
	)
	{
		if(
			sight_range.second.contains(
				_id
			)
		)
		{
			global_context_.send_to_player(
				sight_range.first,
				_msg
			);
		}
	}
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
	sanguis::random_generator_ref const _random_generator,
	sanguis::server::weapons::common_parameters const &_weapon_parameters
)
{
	for(
		sanguis::creator::spawn const &spawn
		:
		_spawns
	)
	{
		switch(
			spawn.spawn_type()
		)
		{
		case sanguis::creator::spawn_type::single:
			this->insert(
				sanguis::server::world::generate_single_spawns(
					spawn.enemy_type(),
					spawn.enemy_kind(),
					spawn.pos(),
					_weapon_parameters,
					_random_generator,
					this->load_context(),
					difficulty_
				)
			);
			continue;
		case sanguis::creator::spawn_type::spawner:
			this->insert(
				sanguis::server::world::make_spawner(
					spawn.enemy_type(),
					spawn.enemy_kind(),
					spawn.pos(),
					_weapon_parameters,
					_random_generator,
					difficulty_
				)
			);
			continue;
		}

		FCPPT_ASSERT_UNREACHABLE;
	}
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
	{
		this->insert(
			sanguis::server::world::generate_destructibles(
				_random_generator,
				destructible,
				this->load_context(),
				difficulty_
			)
		);
	}
}
