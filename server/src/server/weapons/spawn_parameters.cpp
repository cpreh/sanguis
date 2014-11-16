#include <sanguis/server/weapons/parameters.hpp>
#include <sanguis/server/weapons/spawn_parameters.hpp>
#include <sanguis/server/weapons/spawn_weapon.hpp>


sanguis::server::weapons::spawn_parameters::spawn_parameters(
	sanguis::server::weapons::parameters const &_parameters,
	sanguis::server::weapons::spawn_weapon const &_spawn_weapon
)
:
	parameters_{
		_parameters
	},
	spawn_weapon_{
		_spawn_weapon
	}
{
}

sanguis::server::weapons::parameters const &
sanguis::server::weapons::spawn_parameters::parameters() const
{
	return
		parameters_;
}

sanguis::server::weapons::spawn_weapon const &
sanguis::server::weapons::spawn_parameters::spawn_weapon() const
{
	return
		spawn_weapon_;
}
