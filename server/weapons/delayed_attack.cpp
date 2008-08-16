#include "delayed_attack.hpp"

sanguis::server::weapons::delayed_attack::delayed_attack(
	messages::pos_type const &spawn_point_,
	messages::space_unit const angle_,
	team::type const team_,
	messages::pos_type const &dest_)
: spawn_point_(spawn_point_),
  angle_(angle_),
  team_(team_),
  dest_(dest_)
{}

sanguis::messages::pos_type const &
sanguis::server::weapons::delayed_attack::spawn_point() const
{
	return spawn_point_;
}

sanguis::messages::space_unit
sanguis::server::weapons::delayed_attack::angle() const
{
	return angle_;
}

sanguis::server::team::type
sanguis::server::weapons::delayed_attack::team() const
{
	return team_;
}

sanguis::messages::pos_type const &
sanguis::server::weapons::delayed_attack::dest() const
{
	return dest_;
}
