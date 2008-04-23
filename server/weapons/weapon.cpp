#include "weapon.hpp"
#include "../entity.hpp"
#include "../../time_util.hpp"
#include <sge/time.hpp>

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

sanguis::server::weapons::weapon::~weapon()
{}

sanguis::server::weapons::weapon::weapon(
	const send_callback &send_callback_,
	const insert_callback &insert_callback_,
	const messages::space_unit range_,
	const time_type base_cooldown_)
: range_(range_),
  cooldown_timer(
	to_sge_time(
		base_cooldown_)),
  send_callback_(send_callback_),
  insert_callback_(insert_callback_)
{}

void sanguis::server::weapons::weapon::send(messages::base *m)
{
	send_callback_(m);
}

sanguis::server::insert_callback sanguis::server::weapons::weapon::get_insert_callback() const
{
	return insert_callback_;
}

sanguis::server::send_callback sanguis::server::weapons::weapon::get_send_callback() const
{
	return send_callback_;
}

sanguis::server::entity &
sanguis::server::weapons::weapon::insert(entity_ptr e)
{
	return insert_callback_(e);
}

bool sanguis::server::weapons::weapon::in_range(
	entity const& from,
	messages::pos_type const& to) const
{
	return (from.center() - to).length() < range();
}
