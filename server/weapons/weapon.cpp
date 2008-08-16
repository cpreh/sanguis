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

void sanguis::server::weapons::weapon::update(
	time_type const tm)
{
	diff.update(tm);
}

bool sanguis::server::weapons::weapon::attack(
	entities::entity const &from,
	messages::pos_type const& to)
{
	if(!cooldown_timer.update_b() || !in_range(from, to))
		return false;
	
	cast_point_timer.activate();

	do_attack(from, to);
	return true;
}

sanguis::server::weapons::weapon::~weapon()
{}

sanguis::server::weapons::weapon::weapon(
	environment const &env_,
	weapon_type::type const type_,
	messages::space_unit const range_,
	time_type const base_cooldown_,
	time_type const cast_point_)
: diff(),
  env_(env_),
  type_(type_),
  range_(range_),
  cooldown_timer(
  	sge::time::second(base_cooldown_),
	true,
	diff.callback()),
  cast_point_timer(
	sge::time::second(cast_point_),
	false,
	diff.callback())
{}

void sanguis::server::weapons::weapon::send(
	messages::auto_ptr m)
{
	env_.send(m);
}

sanguis::server::environment
sanguis::server::weapons::weapon::get_environment() const
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
