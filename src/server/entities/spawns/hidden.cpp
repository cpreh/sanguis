#include <sanguis/messages/base.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/spawns/hidden.hpp>


sanguis::server::entities::spawns::hidden::hidden()
:
	sanguis::server::entities::base()
{
}

sanguis::server::entities::spawns::hidden::~hidden()
{
}

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

sanguis::messages::unique_ptr
sanguis::server::entities::spawns::hidden::add_message(
	sanguis::server::player_id
) const
{
	return sanguis::messages::unique_ptr();
}
