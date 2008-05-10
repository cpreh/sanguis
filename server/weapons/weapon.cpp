#include "weapon.hpp"
#include "../entities/entity.hpp"
#include <sge/time/second.hpp>

sanguis::messages::space_unit
sanguis::server::weapons::weapon::range() const
{
	return range_;
}

sanguis::weapon_type::type sanguis::server::weapons::weapon::type() const
{
	return type_;
}

bool sanguis::server::weapons::weapon::attack(
	entities::entity const &from,
	messages::pos_type const& to)
{
	if(!cooldown_timer.update_b() || !in_range(from, to))
		return false;
	do_attack(from, to);
	return true;
}

sanguis::server::weapons::weapon::~weapon()
{}

sanguis::server::weapons::weapon::weapon(
	const environment &env_,
	const weapon_type::type type_,
	const messages::space_unit range_,
	const time_type base_cooldown_)
: env_(env_),
	type_(type_),
	range_(range_),
  cooldown_timer(
  	sge::time::second(base_cooldown_))
{}

void sanguis::server::weapons::weapon::send(messages::base *m)
{
	env_.send(m);
}

sanguis::server::environment sanguis::server::weapons::weapon::get_environment() const
{
	return env_;
}

sanguis::server::entities::entity &
sanguis::server::weapons::weapon::insert(
	entities::auto_ptr e)
{
	return env_.insert(e);
}

bool sanguis::server::weapons::weapon::in_range(
	entities::entity const& from,
	messages::pos_type const& to) const
{
	return (from.center() - to).length() < range();
}
