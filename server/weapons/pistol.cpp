#include "pistol.hpp"

sanguis::server::weapons::pistol::pistol(
	const time_type base_cooldown,insert_callback insert)
: weapon(
	1000, // FIXME
	base_cooldown,insert)
{}

void sanguis::server::weapons::pistol::do_attack(
	entity const &from,
	messages::pos_type const &to)
{
	// TODO: spawn melee bullet here
}
