#include "sattelite.hpp"

sanguis::server::entities::sattelite::sattelite(
	entity &_e)
	: e(_e)
{
}

void sanguis::server::entities::sattelite::position_change(
	collision::point const &p)
{
	entity.center(
		sge::math::structure_cast<pos_type::value_type>(
			p));
}

sanguis::server::entities::entity &sanguis::server::entities::sattelite::entity()
{
	return e;
}

sanguis::server::entities::entity const &sanguis::server::entities::sattelite::entity() const
{
	return e;
}
