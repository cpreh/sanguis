#include <sanguis/duration.hpp>
#include <sanguis/magazine_remaining.hpp>
#include <sanguis/perk_type.hpp>
#include <sanguis/player_name.hpp>
#include <sanguis/random_generator_fwd.hpp>
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
#include <sanguis/server/model_size.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/regeneration.hpp>
#include <sanguis/server/remove_sight_callback.hpp>
#include <sanguis/server/remove_weapon_pickup_callback.hpp>
#include <sanguis/server/skill_points.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/team.hpp>
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
#include <sanguis/server/entities/property/current_to_max.hpp>
#include <sanguis/server/entities/property/initial_zero.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/perks/perk.hpp>
#include <sanguis/server/perks/tree/choosable.hpp>
#include <sanguis/server/perks/tree/choose.hpp>
#include <sanguis/server/perks/tree/container.hpp>
#include <sanguis/server/perks/tree/create.hpp>
#include <sanguis/server/perks/tree/status.hpp>
#include <sanguis/server/weapons/default_ias.hpp>
#include <sanguis/server/weapons/default_irs.hpp>
#include <sanguis/server/weapons/optional_unique_ptr.hpp>
#include <sanguis/server/weapons/player_start_weapon.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/atan2.hpp>
#include <fcppt/math/vector/length_square.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::player::player(
	sanguis::random_generator &_random_generator,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::health const _health,
	sanguis::server::damage::armor_array const &_armor,
	sanguis::server::entities::movement_speed const _speed,
	sanguis::player_name const &_name,
	sanguis::server::player_id const _player_id
)
:
	sanguis::server::entities::ifaces::with_team(),
	sanguis::server::entities::with_velocity(
		_load_context.model_size(
			sanguis::load::model::player_path()
		),
		sanguis::server::entities::movement_speed_initial(
			sanguis::server::entities::property::initial_zero(
				_speed.get()
			)
		),
		sanguis::server::direction(
			0.f
		)
	),
	sanguis::server::entities::with_auras_id(
		fcppt::assign::make_container<
			sanguis::server::auras::container
		>(
			fcppt::make_unique_ptr<
				sanguis::server::auras::update_sight
			>(
				sanguis::server::radius(
					2000.f
				),
				sanguis::server::add_sight_callback(
					std::bind(
						&sanguis::server::entities::player::add_sight_range,
						this,
						std::placeholders::_1,
						std::placeholders::_2
					)
				),
				sanguis::server::remove_sight_callback(
					std::bind(
						&sanguis::server::entities::player::remove_sight_range,
						this,
						std::placeholders::_1
					)
				)
			)
		)(
			fcppt::make_unique_ptr<
				sanguis::server::auras::weapon_pickup_candidates
			>(
				// with_velocity needs to be initialized first!
				this->radius(),
				sanguis::server::add_weapon_pickup_callback(
					std::bind(
						&sanguis::server::entities::player::weapon_pickup_add_candidate,
						this,
						std::placeholders::_1
					)
				),
				sanguis::server::remove_weapon_pickup_callback(
					std::bind(
						&sanguis::server::entities::player::weapon_pickup_remove_candidate,
						this,
						std::placeholders::_1
					)
				)
			)
		).move_container()
	),
	sanguis::server::entities::with_buffs(),
	sanguis::server::entities::with_id(
		_load_context.next_id()
	),
	sanguis::server::entities::with_health(
		_health,
		sanguis::server::regeneration(
			0.f
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
				_random_generator
			)
		),
		sanguis::server::weapons::default_ias(),
		sanguis::server::weapons::default_irs()
	),
	name_(
		_name
	),
	player_id_(
		_player_id
	),
	exp_(
		0.f
	),
	level_(
		0u
	),
	skill_points_(
		0u
	),
	perk_tree_(
		sanguis::server::perks::tree::create()
	),
	desired_speed_(
		sanguis::server::speed::value_type::null()
	),
	weapon_pickups_()
{
}

sanguis::server::entities::player::~player()
{
}

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

	this->environment()->exp_changed(
		this->player_id(),
		exp_
	);

	sanguis::server::level const
		old_level(
			level_
		),
		new_level(
			sanguis::server::level_from_exp(
				exp_
			)
		);

	if(
		new_level == old_level
	)
		return;

	skill_points_ +=
		sanguis::server::skill_points(
			new_level.get()
			-
			old_level.get()
		);

	level_ = new_level;

	this->environment()->level_changed(
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
		skill_points_.get() > 0u
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
	sanguis::server::speed const _speed
)
{
	desired_speed_ = _speed;

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

	typedef
	fcppt::optional<
		sanguis::server::entities::pickups::weapon &
	>
	result_type;

	result_type const closest_pickup(
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
		)
	);

	if(
		closest_pickup
	)
		this->pickup_weapon(
			closest_pickup->obtain()
		);

	if(
		dropped
	)
		this->environment()->insert(
			fcppt::make_unique_ptr<
				sanguis::server::entities::pickups::weapon
			>(
				this->environment()->load_context(),
				this->team(),
				std::move(
					*dropped
				)
			),
			sanguis::server::entities::insert_parameters_center(
				this->center()
			)
		);
}

sanguis::server::perks::tree::container const &
sanguis::server::entities::player::perk_tree() const
{
	return
		perk_tree_;
}

sanguis::server::skill_points const
sanguis::server::entities::player::skill_points() const
{
	return
		skill_points_;
}

sanguis::server::player_id const
sanguis::server::entities::player::player_id() const
{
	return
		player_id_;
}

sanguis::server::level const
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
sanguis::server::entities::player::remove()
{
	this->environment()->remove_player(
		this->player_id()
	);
}

void
sanguis::server::entities::player::update_speed()
{
	if(
		fcppt::math::vector::length_square(
			desired_speed_.get()
		)
		<
		fcppt::literal<
			sanguis::server::space_unit
		>(
			0.001f
		)
	)
	{
		this->movement_speed().current(
			fcppt::literal<
				sanguis::server::space_unit
			>(
				0
			)
		);

		return;
	}

	this->direction(
		sanguis::server::direction(
			fcppt::math::vector::atan2(
				desired_speed_.get()
			)
		)
	);

	// TODO: don't set the speed to max!
	// Allow for controls that are not binary
	sanguis::server::entities::property::current_to_max(
		this->movement_speed()
	);
}

void
sanguis::server::entities::player::add_sight_range(
	sanguis::server::entities::with_id const &_entity,
	sanguis::collision::world::created const _created
)
{
	this->environment()->add_sight_range(
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
	this->environment()->remove_sight_range(
		this->player_id(),
		_entity
	);
}

void
sanguis::server::entities::player::weapon_pickup_add_candidate(
	sanguis::server::entities::pickups::weapon &_entity
)
{
	FCPPT_ASSERT_ERROR(
		weapon_pickups_.insert(
			fcppt::make_ref(
				_entity
			)
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
		1u
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
			Message(
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
	this->environment()->got_weapon(
		this->player_id(),
		_weapon.description()
	);
}

void
sanguis::server::entities::player::on_drop_weapon(
	sanguis::is_primary_weapon const _is_primary
)
{
	this->environment()->remove_weapon(
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
	this->environment()->magazine_remaining(
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
	this->environment()->reload_time(
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
