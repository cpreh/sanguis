#include "weapon.hpp"
#include "../entity.hpp"

sanguis::messages::space_unit
sanguis::server::weapons::weapon::range() const
{
	return range_;
}

bool sanguis::server::weapons::weapon::attack(
	entity const &from,
	messages::pos_type const& to)
{
	if(!cooldown_timer.update_b() || !in_range(from, to))
		return false;
	do_attack(from, to);
	return true;
}
sanguis::server::weapons::weapon::weapon(
	const messages::space_unit range_,
	const time_type base_cooldown_,
	insert_callback insert_)
: range_(range_),
  cooldown_timer(base_cooldown_),
	insert_(insert_)
{}

sanguis::server::entity &sanguis::server::weapons::weapon::insert(entity_ptr e)
{
	return insert_(e);
}

bool sanguis::server::weapons::weapon::in_range(
	entity const& from,
	messages::pos_type const& to) const
{
	return (from.center() - to).length() < range();
}
