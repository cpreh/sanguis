#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/damage/armor.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/spawn_owner.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::enemies::parameters::parameters(
	sanguis::diff_clock const &_diff_clock,
	sanguis::creator::enemy_type const _enemy_type,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::damage::armor const &_armor,
	sanguis::server::health const _health,
	sanguis::server::entities::movement_speed const _movement_speed,
	sanguis::server::ai::create_function const &_ai_create_function,
	sanguis::server::weapons::unique_ptr &&_weapon,
	sanguis::server::pickup_probability const _pickup_probability,
	sanguis::server::exp const _exp,
	sanguis::server::entities::enemies::difficulty const _difficulty,
	sanguis::server::entities::enemies::spawn_owner const &_spawn_owner,
	sanguis::server::auras::container &&_auras
)
:
	diff_clock_(
		_diff_clock
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
	)
{
}

sanguis::server::entities::enemies::parameters::parameters(
	parameters &&
) = default;

sanguis::server::entities::enemies::parameters::~parameters()
{
}

sanguis::diff_clock const &
sanguis::server::entities::enemies::parameters::diff_clock() const
{
	return
		diff_clock_;
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

sanguis::server::damage::armor const &
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

sanguis::server::entities::enemies::spawn_owner const &
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