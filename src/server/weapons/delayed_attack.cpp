#include "delayed_attack.hpp"
#include <fcppt/math/vector/basic_impl.hpp>

sanguis::server::weapons::delayed_attack::delayed_attack(
	pos_type const &_spawn_point,
	space_unit const _angle,
	team::type const _team,
	server::environment::object_ptr const _environment,
	pos_type const &_dest
)
:
	spawn_point_(_spawn_point),
	angle_(_angle),
	team_(_team),
	environment_(_environment),
	dest_(_dest)
{}

sanguis::server::pos_type const &
sanguis::server::weapons::delayed_attack::spawn_point() const
{
	return spawn_point_;
}

sanguis::server::space_unit
sanguis::server::weapons::delayed_attack::angle() const
{
	return angle_;
}

sanguis::server::team::type
sanguis::server::weapons::delayed_attack::team() const
{
	return team_;
}

sanguis::server::environment::object_ptr const
sanguis::server::weapons::delayed_attack::environment() const
{
	return environment_;
}

sanguis::server::pos_type const &
sanguis::server::weapons::delayed_attack::dest() const
{
	return dest_;
}
