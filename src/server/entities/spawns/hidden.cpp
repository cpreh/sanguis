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
