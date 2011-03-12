#include "hidden.hpp"
#include "../../../messages/base.hpp"

sanguis::server::entities::spawns::hidden::hidden()
:
	base()
{}

bool
sanguis::server::entities::spawns::hidden::dead() const
{
	return false;
}

bool
sanguis::server::entities::spawns::hidden::invulnerable() const
{
	return true;
}

bool
sanguis::server::entities::spawns::hidden::server_only() const
{
	return true;
}

sanguis::messages::auto_ptr
sanguis::server::entities::spawns::hidden::add_message(
	player_id
) const
{
	return messages::auto_ptr();
}
