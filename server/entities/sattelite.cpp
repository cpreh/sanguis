#include "sattelite.hpp"
#include "entity.hpp"
#include "../types.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>

sanguis::server::entities::sattelite::sattelite(
	sanguis::server::entities::entity &_e)
:
	e(_e)
{
}

void
sanguis::server::entities::sattelite::position_change(
	sge::collision::point const &p)
{
	e.collision_update(
		pos_type(
			static_cast<pos_type::value_type>(p.x()),
			static_cast<pos_type::value_type>(p.y())));
}

sanguis::server::entities::entity &
sanguis::server::entities::sattelite::entity()
{
	return e;
}

sanguis::server::entities::entity const &
sanguis::server::entities::sattelite::entity() const
{
	return e;
}
