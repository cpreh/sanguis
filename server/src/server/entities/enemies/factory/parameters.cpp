#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/special_chance.hpp>
#include <sanguis/server/entities/enemies/factory/parameters.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>


sanguis::server::entities::enemies::factory::parameters::parameters(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::creator::enemy_type const _enemy_type,
	sanguis::server::entities::enemies::difficulty const _difficulty,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::entities::spawn_owner const &_spawn_owner,
	sanguis::server::entities::enemies::special_chance const _special_chance
)
:
	diff_clock_(
		_diff_clock
	),
	random_generator_(
		_random_generator
	),
	enemy_type_(
		_enemy_type
	),
	difficulty_(
		_difficulty
	),
	load_context_(
		_load_context
	),
	spawn_owner_(
		_spawn_owner
	),
	special_chance_(
		_special_chance
	)
{
}

sanguis::diff_clock const &
sanguis::server::entities::enemies::factory::parameters::diff_clock() const
{
	return
		diff_clock_;
}

sanguis::random_generator &
sanguis::server::entities::enemies::factory::parameters::random_generator() const
{
	return
		random_generator_;
}

sanguis::creator::enemy_type
sanguis::server::entities::enemies::factory::parameters::enemy_type() const
{
	return
		enemy_type_;
}

sanguis::server::entities::enemies::difficulty const
sanguis::server::entities::enemies::factory::parameters::difficulty() const
{
	return
		difficulty_;
}

sanguis::server::environment::load_context &
sanguis::server::entities::enemies::factory::parameters::load_context() const
{
	return
		load_context_;
}

sanguis::server::entities::spawn_owner const &
sanguis::server::entities::enemies::factory::parameters::spawn_owner() const
{
	return
		spawn_owner_;
}

sanguis::server::entities::enemies::special_chance const
sanguis::server::entities::enemies::factory::parameters::special_chance() const
{
	return
		special_chance_;
}
