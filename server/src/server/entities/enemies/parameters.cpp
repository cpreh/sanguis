#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/regeneration.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/auras/unique_ptr.hpp>
#include <sanguis/server/damage/armor_array.hpp>
#include <sanguis/server/damage/armor_unit.hpp>
#include <sanguis/server/damage/type.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/weapons/default_ias.hpp>
#include <sanguis/server/weapons/default_irs.hpp>
#include <sanguis/server/weapons/ias.hpp>
#include <sanguis/server/weapons/irs.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::enemies::parameters::parameters(
	sanguis::random_generator &_random_generator,
	sanguis::creator::enemy_type const _enemy_type,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::damage::armor_array const &_armor,
	sanguis::server::health const _health,
	sanguis::server::entities::movement_speed const _movement_speed,
	sanguis::server::ai::create_function const &_ai_create_function,
	sanguis::server::weapons::unique_ptr &&_weapon,
	sanguis::server::pickup_probability const _pickup_probability,
	sanguis::server::exp const _exp,
	sanguis::server::entities::enemies::difficulty const _difficulty,
	sanguis::server::entities::spawn_owner const &_spawn_owner,
	sanguis::server::auras::container &&_auras
)
:
	random_generator_(
		_random_generator
	),
	enemy_type_(
		_enemy_type
	),
	load_context_(
		_load_context
	),
	armor_(
		_armor
	),
	health_(
		_health
	),
	regeneration_(
		fcppt::literal<
			sanguis::server::regeneration::value_type
		>(
			0
		)
	),
	movement_speed_(
		_movement_speed
	),
	ai_create_function_(
		_ai_create_function
	),
	weapon_(
		std::move(
			_weapon
		)
	),
	pickup_probability_(
		_pickup_probability
	),
	exp_(
		_exp
	),
	difficulty_(
		_difficulty
	),
	spawn_owner_(
		_spawn_owner
	),
	auras_(
		std::move(
			_auras
		)
	),
	ias_(
		sanguis::server::weapons::default_ias()
	),
	irs_(
		sanguis::server::weapons::default_irs()
	)
{
}

sanguis::server::entities::enemies::parameters::parameters(
	parameters &&
) = default;

sanguis::server::entities::enemies::parameters::~parameters()
{
}

sanguis::random_generator &
sanguis::server::entities::enemies::parameters::random_generator() const
{
	return
		random_generator_;
}

sanguis::creator::enemy_type
sanguis::server::entities::enemies::parameters::enemy_type() const
{
	return
		enemy_type_;
}

sanguis::server::environment::load_context &
sanguis::server::entities::enemies::parameters::load_context() const
{
	return
		load_context_;
}

sanguis::server::damage::armor_array const &
sanguis::server::entities::enemies::parameters::armor() const
{
	return
		armor_;
}

sanguis::server::health const
sanguis::server::entities::enemies::parameters::health() const
{
	return
		health_;
}

sanguis::server::regeneration const
sanguis::server::entities::enemies::parameters::regeneration() const
{
	return
		regeneration_;
}

sanguis::server::entities::movement_speed const
sanguis::server::entities::enemies::parameters::movement_speed() const
{
	return
		movement_speed_;
}

sanguis::server::ai::create_function const &
sanguis::server::entities::enemies::parameters::ai_create_function() const
{
	return
		ai_create_function_;
}

sanguis::server::weapons::unique_ptr &
sanguis::server::entities::enemies::parameters::weapon()
{
	return
		weapon_;
}

sanguis::server::pickup_probability const
sanguis::server::entities::enemies::parameters::pickup_probability() const
{
	return
		pickup_probability_;
}

sanguis::server::exp const
sanguis::server::entities::enemies::parameters::exp() const
{
	return
		exp_;
}

sanguis::server::entities::enemies::difficulty const
sanguis::server::entities::enemies::parameters::difficulty() const
{
	return
		difficulty_;
}

sanguis::server::entities::spawn_owner const &
sanguis::server::entities::enemies::parameters::spawn_owner() const
{
	return
		spawn_owner_;
}

sanguis::server::auras::container &
sanguis::server::entities::enemies::parameters::auras()
{
	return
		auras_;
}

sanguis::server::weapons::ias const
sanguis::server::entities::enemies::parameters::ias() const
{
	return
		ias_;
}

sanguis::server::weapons::irs const
sanguis::server::entities::enemies::parameters::irs() const
{
	return
		irs_;
}

sanguis::server::entities::enemies::parameters &
sanguis::server::entities::enemies::parameters::health(
	sanguis::server::health const _health
)
{
	health_ =
		_health;

	return
		*this;
}

sanguis::server::entities::enemies::parameters &
sanguis::server::entities::enemies::parameters::regeneration(
	sanguis::server::regeneration const _regeneration
)
{
	regeneration_ =
		_regeneration;

	return
		*this;
}

sanguis::server::entities::enemies::parameters &
sanguis::server::entities::enemies::parameters::movement_speed(
	sanguis::server::entities::movement_speed const _movement_speed
)
{
	movement_speed_ =
		_movement_speed;

	return
		*this;
}

sanguis::server::entities::enemies::parameters &
sanguis::server::entities::enemies::parameters::pickup_probability(
	sanguis::server::pickup_probability const _pickup_probability
)
{
	pickup_probability_ =
		_pickup_probability;

	return
		*this;
}

sanguis::server::entities::enemies::parameters &
sanguis::server::entities::enemies::parameters::exp(
	sanguis::server::exp const _exp
)
{
	exp_ =
		_exp;

	return
		*this;
}

sanguis::server::entities::enemies::parameters &
sanguis::server::entities::enemies::parameters::difficulty(
	sanguis::server::entities::enemies::difficulty const _difficulty
)
{
	difficulty_ =
		_difficulty;

	return
		*this;
}

sanguis::server::entities::enemies::parameters &
sanguis::server::entities::enemies::parameters::ias(
	sanguis::server::weapons::ias const _ias
)
{
	ias_
		= _ias;

	return
		*this;
}

sanguis::server::entities::enemies::parameters &
sanguis::server::entities::enemies::parameters::irs(
	sanguis::server::weapons::irs const _irs
)
{
	irs_
		= _irs;

	return
		*this;
}

sanguis::server::entities::enemies::parameters &
sanguis::server::entities::enemies::parameters::add_aura(
	sanguis::server::auras::unique_ptr &&_aura
)
{
	auras_.push_back(
		std::move(
			_aura
		)
	);

	return
		*this;
}

sanguis::server::entities::enemies::parameters &
sanguis::server::entities::enemies::parameters::armor_element(
	sanguis::server::damage::type const _type,
	sanguis::server::damage::armor_unit const _unit
)
{
	armor_[
		_type
	] =
		_unit;

	return
		*this;
}
