#include "from_sge_pos.hpp"
#include <fcppt/math/vecfromr/basic_impl.hpp>
#include <fcppt/math/vecfromr/structure_cast.hpp>

sanguis::server::pos const
sanguis::server::collision::from_sge_pos(
	sge::projectile::vector2 const &_pos
)
{
	return
		fcppt::math::vector::structure_cast<
			sge::projectile::vector2
		>(
			_pos
		);
}
