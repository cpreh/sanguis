#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/weapons/target.hpp>


sanguis::server::weapons::delayed_attack::delayed_attack(
	sanguis::server::center const _spawn_point,
	sanguis::server::angle const _angle,
	sanguis::server::team const _team,
	sanguis::server::environment::object &_environment,
	sanguis::server::weapons::target const _target
)
:
	spawn_point_(
		_spawn_point
	),
	angle_(
		_angle
	),
	team_(
		_team
	),
	environment_(
		_environment
	),
	target_(
		_target
	)
{
}

sanguis::server::center const &
sanguis::server::weapons::delayed_attack::spawn_point() const
{
	return spawn_point_;
}

sanguis::server::angle const
sanguis::server::weapons::delayed_attack::angle() const
{
	return angle_;
}

sanguis::server::team
sanguis::server::weapons::delayed_attack::team() const
{
	return team_;
}

sanguis::server::environment::object &
sanguis::server::weapons::delayed_attack::environment() const
{
	return environment_;
}

sanguis::server::weapons::target const &
sanguis::server::weapons::delayed_attack::target() const
{
	return target_;
}
