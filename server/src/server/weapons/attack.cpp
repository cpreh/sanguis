#include <sanguis/server/angle.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/weapons/attack.hpp>
#include <sanguis/server/weapons/target.hpp>


sanguis::server::weapons::attack::attack(
	sanguis::server::angle const _angle,
	sanguis::server::environment::object &_environment,
	sanguis::server::weapons::target const _target
)
:
	angle_(
		_angle
	),
	environment_(
		_environment
	),
	target_(
		_target
	)
{
}

sanguis::server::angle
sanguis::server::weapons::attack::angle() const
{
	return
		angle_;
}

sanguis::server::environment::object &
sanguis::server::weapons::attack::environment() const
{
	return
		environment_.get();
}

sanguis::server::weapons::target const &
sanguis::server::weapons::attack::target() const
{
	return
		target_;
}
