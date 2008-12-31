#include "distance.hpp"
#include "entities/entity.hpp"

sanguis::server::space_unit
sanguis::server::distance(
	entities::entity const &a,
	entities::entity const &b)
{
	return distance(a, b.center());
}

sanguis::server::space_unit
sanguis::server::distance(
	entities::entity const &a,
	pos_type const &b)
{
	return (a.center() - b).length();
}
