#include "weapon.hpp"

sanguis::server::weapons::weapon::weapon(
	const messages::space_unit range_,
	const time_type base_cooldown_)
: range_(range_),
  base_cooldown_(base_cooldown_)
{}

sanguis::messages::space_unit
sanguis::server::weapons::weapon::range() const
{
	return range_;
}

sanguis::time_type
sanguis::server::weapons::weapon::base_cooldown() const
{
	return base_cooldown_;
}
