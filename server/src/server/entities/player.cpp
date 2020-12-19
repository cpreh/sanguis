#include <sanguis/duration.hpp>
#include <sanguis/magazine_remaining.hpp>
#include <sanguis/perk_type.hpp>
#include <sanguis/player_name.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/weapon_type_to_is_primary.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/load/model/player_path.hpp>
#include <sanguis/messages/roles/angle.hpp>
#include <sanguis/messages/roles/aura_type_container.hpp>
#include <sanguis/messages/roles/buff_type_container.hpp>
#include <sanguis/messages/roles/center.hpp>
#include <sanguis/messages/roles/created.hpp>
#include <sanguis/messages/roles/entity_id.hpp>
#include <sanguis/messages/roles/health.hpp>
#include <sanguis/messages/roles/max_health.hpp>
#include <sanguis/messages/roles/name.hpp>
#include <sanguis/messages/roles/primary_weapon.hpp>
#include <sanguis/messages/roles/speed.hpp>
#include <sanguis/messages/roles/weapon_status.hpp>
#include <sanguis/messages/server/add_own_player.hpp>
#include <sanguis/messages/server/add_player.hpp>
#include <sanguis/messages/server/base.hpp>
#include <sanguis/messages/server/create_ptr.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/add_sight_callback.hpp>
#include <sanguis/server/add_weapon_pickup_callback.hpp>
#include <sanguis/server/closest_entity.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/level_from_exp.hpp>
#include <sanguis/server/optional_mass.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/regeneration.hpp>
#include <sanguis/server/remove_sight_callback.hpp>
#include <sanguis/server/remove_weapon_pickup_callback.hpp>
#include <sanguis/server/skill_points.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/auras/update_sight.hpp>
#include <sanguis/server/auras/weapon_pickup_candidates.hpp>
#include <sanguis/server/damage/armor_array_fwd.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/movement_speed_initial.hpp>
#include <sanguis/server/entities/player.hpp>
#include <sanguis/server/entities/with_auras_id.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/with_perks.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/entities/pickups/weapon.hpp>
#include <sanguis/server/entities/pickups/weapon_ref.hpp>
#include <sanguis/server/entities/property/current_to_max.hpp>
#include <sanguis/server/entities/property/initial_zero.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/environment/optional_object_ref.hpp>
#include <sanguis/server/perks/perk.hpp>
#include <sanguis/server/perks/tree/choosable.hpp>
#include <sanguis/server/perks/tree/choose.hpp>
#include <sanguis/server/perks/tree/container.hpp>
#include <sanguis/server/perks/tree/create.hpp>
#include <sanguis/server/perks/tree/status.hpp>
#include <sanguis/server/weapons/common_parameters_fwd.hpp>
#include <sanguis/server/weapons/default_ias.hpp>
#include <sanguis/server/weapons/default_irs.hpp>
#include <sanguis/server/weapons/optional_unique_ptr.hpp>
#include <sanguis/server/weapons/player_start_weapon.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <alda/message/init_record.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/container/make.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/atan2.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::server::entities::player::player(
	sanguis::random_generator_ref const _random_generator,
	sanguis::server::weapons::common_parameters const &_weapon_parameters,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::health const _health,
	sanguis::server::damage::armor_array const &_armor,
	sanguis::server::entities::movement_speed const _speed,
	sanguis::player_name &&_name,
	sanguis::server::player_id const _player_id
)
:
	sanguis::server::entities::ifaces::with_team(),
	sanguis::server::entities::with_velocity(
		_load_context.model_size(
			sanguis::load::model::player_path()
		),
		sanguis::server::optional_mass(),
		sanguis::server::entities::movement_speed_initial(
			sanguis::server::entities::property::initial_zero(
				_speed.get()
			)
		),
		sanguis::server::direction(
			0.F
		)
	),
	sanguis::server::entities::with_auras_id(
		fcppt::container::make<
			sanguis::server::auras::container
		>(
			fcppt::unique_ptr_to_base<
				sanguis::server::auras::aura
			>(
				fcppt::make_unique_ptr<
					sanguis::server::auras::update_sight
				>(
					sanguis::server::radius(
						2000.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
					),
					sanguis::server::add_sight_callback(
						[
							this
						](
							sanguis::server::entities::with_id const &_entity,
							sanguis::collision::world::created const _created
						)
						{
							this->add_sight_range(
								_entity,
								_created
							);
						}
					),
					sanguis::server::remove_sight_callback(
						[
							this
						](
							sanguis::server::entities::with_id const &_entity
						)
						{
							this->remove_sight_range(
								_entity
							);
						}
					)
				)
			),
			fcppt::unique_ptr_to_base<
				sanguis::server::auras::aura
			>(
				fcppt::make_unique_ptr<
					sanguis::server::auras::weapon_pickup_candidates
				>(
					// with_velocity needs to be initialized first!
					this->radius(),
					sanguis::server::add_weapon_pickup_callback{
						[
							this
						](
							sanguis::server::entities::pickups::weapon_ref const _entity
						)
						{
							this->weapon_pickup_add_candidate(
								_entity
							);
						}
					},
					sanguis::server::remove_weapon_pickup_callback{
						[
							this
						](
							sanguis::server::entities::pickups::weapon &_entity
						)
						{
							this->weapon_pickup_remove_candidate(
								_entity
							);
						}
					}
				)
			)
		)
	),
	sanguis::server::entities::with_buffs(),
	sanguis::server::entities::with_id(
		_load_context.next_id()
	),
	sanguis::server::entities::with_health(
		_health,
		sanguis::server::regeneration(
			0.F
		),
		_armor
	),
	sanguis::server::entities::with_links(),
	sanguis::server::entities::with_perks(
		_random_generator
	),
	sanguis::server::entities::with_weapon(
		sanguis::server::weapons::optional_unique_ptr(
			sanguis::server::weapons::player_start_weapon(
				_weapon_parameters
			)
		),
		sanguis::server::weapons::default_ias(),
		sanguis::server::weapons::default_irs()
	),
	name_(
		std::move(
			_name
		)
	),
	player_id_(
		_player_id
	),
	exp_(
		0.F
	),
	level_(
		0U
	),
	skill_points_(
		0U
	),
	perk_tree_(
		sanguis::server::perks::tree::create()
	),
	desired_speed_(
		fcppt::math::vector::null<
			sanguis::server::speed::value_type
		>()
	),
	weapon_pickups_()
{
}

FCPPT_PP_POP_WARNING

sanguis::server::entities::player::~player()
= default;

void
sanguis::server::entities::player::add_exp(
	sanguis::server::exp const _exp
)
{
	exp_ =
		sanguis::server::exp(
			exp_.get()
			+ _exp.get()
		);

	FCPPT_ASSERT_OPTIONAL_ERROR(
		this->environment()
	).get().exp_changed(
		this->player_id(),
		exp_
	);

	sanguis::server::level const old_level{
		level_
	};

	sanguis::server::level const new_level{
		sanguis::server::level_from_exp(
			exp_
		)
	};

	if(
		new_level == old_level
	)
	{
		return;
	}

	skill_points_ +=
		sanguis::server::skill_points(
			new_level.get()
			-
			old_level.get()
		);

	level_ = new_level;

	FCPPT_ASSERT_OPTIONAL_ERROR(
		this->environment()
	).get().level_changed(
		this->player_id(),
		level_
	);
}

sanguis::player_name const &
sanguis::server::entities::player::name() const
{
	return
		name_;
}

bool
sanguis::server::entities::player::perk_choosable(
	sanguis::perk_type const _perk
) const
{
	return
		skill_points_.get() > 0U
		&&
		sanguis::server::perks::tree::choosable(
			perk_tree_,
			_perk,
			level_
		);
}

void
sanguis::server::entities::player::add_perk(
	sanguis::perk_type const _type
)
{
	sanguis::server::perks::tree::choose(
		perk_tree_,
		_type
	);

	sanguis::server::entities::with_perks::add_perk(
		_type
	);

	--skill_points_;
}

void
sanguis::server::entities::player::change_speed(
	sanguis::server::speed const &_speed
)
{
	desired_speed_ =
		_speed;

	this->update_speed();
}

void
sanguis::server::entities::player::drop_or_pickup_weapon(
	sanguis::is_primary_weapon const _is_primary
)
{
	sanguis::server::weapons::optional_unique_ptr dropped(
		this->drop_weapon(
			_is_primary
		)
	);

	fcppt::optional::maybe_void(
		sanguis::server::closest_entity(
			*this,
			weapon_pickups_,
			[
				_is_primary
			](
				sanguis::server::entities::pickups::weapon const &_pickup
			)
			{
				return
					sanguis::weapon_type_to_is_primary(
						_pickup.weapon_type()
					)
					==
					_is_primary
					;
			}
		),
		[
			this
		](
			fcppt::reference<
				sanguis::server::entities::pickups::weapon
			> const _pickup
		)
		{
			this->pickup_weapon(
				_pickup.get().obtain()
			);
		}
	);

	fcppt::optional::maybe_void(
		std::move(
			dropped
		),
		[
			this
		](
			sanguis::server::weapons::unique_ptr &&_dropped
		)
		{
			sanguis::server::environment::optional_object_ref const opt_env{
				this->environment()
			};

			sanguis::server::environment::object &cur_environment(
				FCPPT_ASSERT_OPTIONAL_ERROR(
					opt_env
				).get()
			);

			sanguis::server::environment::insert_no_result(
				cur_environment,
				fcppt::unique_ptr_to_base<
					sanguis::server::entities::with_id
				>(
					fcppt::make_unique_ptr<
						sanguis::server::entities::pickups::weapon
					>(
						cur_environment.load_context(),
						this->team(),
						std::move(
							_dropped
						)
					)
				),
				sanguis::server::entities::insert_parameters_center(
					this->center()
				)
			);
		}
	);
}

sanguis::server::perks::tree::container const &
sanguis::server::entities::player::perk_tree() const
{
	return
		perk_tree_;
}

sanguis::server::skill_points
sanguis::server::entities::player::skill_points() const
{
	return
		skill_points_;
}

sanguis::server::player_id
sanguis::server::entities::player::player_id() const
{
	return
		player_id_;
}

sanguis::server::level
sanguis::server::entities::player::level() const
{
	return
		level_;
}

sanguis::server::team
sanguis::server::entities::player::team() const
{
	return
		sanguis::server::team::players;
}

void
sanguis::server::entities::player::transfer_to_world()
{
	FCPPT_ASSERT_OPTIONAL_ERROR(
		this->environment()
	).get().player_insertion(
		this->player_id()
	);
}

void
sanguis::server::entities::player::remove_from_game()
{
	FCPPT_ASSERT_OPTIONAL_ERROR(
		this->environment()
	).get().remove_player(
		this->player_id()
	);
}

void
sanguis::server::entities::player::update_speed()
{
	fcppt::optional::maybe(
		fcppt::math::vector::atan2(
			desired_speed_.get()
		),
		[
			this
		]{
			this->movement_speed().current(
				fcppt::literal<
					sanguis::server::space_unit
				>(
					0
				)
			);
		},
		[
			this
		](
			sanguis::server::space_unit const _dir
		)
		{
			this->direction(
				sanguis::server::direction(
					_dir
				)
			);

			// TODO(philipp): don't set the speed to max!
			// Allow for controls that are not binary
			sanguis::server::entities::property::current_to_max(
				this->movement_speed()
			);
		}
	);
}

void
sanguis::server::entities::player::add_sight_range(
	sanguis::server::entities::with_id const &_entity,
	sanguis::collision::world::created const _created
)
{
	FCPPT_ASSERT_OPTIONAL_ERROR(
		this->environment()
	).get().add_sight_range(
		this->player_id(),
		_entity,
		_created
	);
}

void
sanguis::server::entities::player::remove_sight_range(
	sanguis::server::entities::with_id const &_entity
)
{
	FCPPT_ASSERT_OPTIONAL_ERROR(
		this->environment()
	).get().remove_sight_range(
		this->player_id(),
		_entity
	);
}

void
sanguis::server::entities::player::weapon_pickup_add_candidate(
	sanguis::server::entities::pickups::weapon_ref const _entity
)
{
	FCPPT_ASSERT_ERROR(
		weapon_pickups_.insert(
			_entity
		)
		.second
	);
}

void
sanguis::server::entities::player::weapon_pickup_remove_candidate(
	sanguis::server::entities::pickups::weapon &_entity
)
{
	FCPPT_ASSERT_ERROR(
		weapon_pickups_.erase(
			fcppt::make_ref(
				_entity
			)
		)
		==
		1U
	);
}

void
sanguis::server::entities::player::update()
{
	sanguis::server::entities::with_buffs::update();

	sanguis::server::entities::with_health::update();

	sanguis::server::entities::with_perks::update();

	sanguis::server::entities::with_velocity::update();

	sanguis::server::entities::with_weapon::update();

	this->update_speed();
}

sanguis::messages::server::unique_ptr
sanguis::server::entities::player::add_message(
	sanguis::server::player_id const _receiver,
	sanguis::collision::world::created const _created
) const
{
	return
		_receiver
		==
		this->player_id()
		?
			this->add_message_impl<
				sanguis::messages::server::add_own_player
			>(
				_created
			)
		:
			this->add_message_impl<
				sanguis::messages::server::add_player
			>(
				_created
			)
		;
}

template<
	typename Message
>
sanguis::messages::server::unique_ptr
sanguis::server::entities::player::add_message_impl(
	sanguis::collision::world::created const _created
) const
{
	return
		sanguis::messages::server::create_ptr(
			alda::message::init_record<
				Message
			>(
				sanguis::messages::roles::entity_id{} =
					this->id(),
				sanguis::messages::roles::center{} =
					this->center().get(),
				sanguis::messages::roles::angle{} =
					this->angle().get(),
				sanguis::messages::roles::created{} =
					_created.get(),
				sanguis::messages::roles::speed{} =
					this->speed().get(),
				sanguis::messages::roles::health{} =
					this->current_health().get(),
				sanguis::messages::roles::max_health{} =
					this->max_health().get(),
				sanguis::messages::roles::primary_weapon{} =
					this->primary_weapon_type(),
				sanguis::messages::roles::weapon_status{} =
					this->weapon_status(),
				sanguis::messages::roles::aura_type_container{} =
					this->aura_types(),
				sanguis::messages::roles::buff_type_container{} =
					this->buff_types(),
				sanguis::messages::roles::name{} =
					sge::charconv::fcppt_string_to_utf8(
						this->name().get()
					)
			)
		);
}

void
sanguis::server::entities::player::on_new_weapon(
	sanguis::server::weapons::weapon const &_weapon
)
{
	FCPPT_ASSERT_OPTIONAL_ERROR(
		this->environment()
	).get().got_weapon(
		this->player_id(),
		_weapon.description()
	);
}

void
sanguis::server::entities::player::on_drop_weapon(
	sanguis::is_primary_weapon const _is_primary
)
{
	FCPPT_ASSERT_OPTIONAL_ERROR(
		this->environment()
	).get().remove_weapon(
		this->player_id(),
		_is_primary
	);
}

void
sanguis::server::entities::player::on_magazine_remaining(
	sanguis::is_primary_weapon const _is_primary,
	sanguis::magazine_remaining const _magazine_remaining
)
{
	FCPPT_ASSERT_OPTIONAL_ERROR(
		this->environment()
	).get().magazine_remaining(
		this->player_id(),
		_is_primary,
		_magazine_remaining
	);
}

void
sanguis::server::entities::player::on_reload_time(
	sanguis::is_primary_weapon const _is_primary,
	sanguis::duration const _reload_time
)
{
	FCPPT_ASSERT_OPTIONAL_ERROR(
		this->environment()
	).get().reload_time(
		this->player_id(),
		_is_primary,
		_reload_time
	);
}

sanguis::collision::world::body_group
sanguis::server::entities::player::collision_group() const
{
	return
		sanguis::collision::world::body_group::player;
}
