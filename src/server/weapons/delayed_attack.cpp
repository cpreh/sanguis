#include <sanguis/server/weapons/delayed_attack.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

sanguis::server::weapons::delayed_attack::delayed_attack(
	server::center const &_spawn_point,
	server::angle const _angle,
	server::team::type const _team,
	server::environment::object &_environment,
	server::vector const &_dest
)
:
	spawn_point_(_spawn_point),
	angle_(_angle),
	team_(_team),
	environment_(_environment),
	dest_(_dest)
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

sanguis::server::team::type
sanguis::server::weapons::delayed_attack::team() const
{
	return team_;
}

sanguis::server::environment::object &
sanguis::server::weapons::delayed_attack::environment() const
{
	return environment_;
}

sanguis::server::vector const &
sanguis::server::weapons::delayed_attack::dest() const
{
	return dest_;
}
