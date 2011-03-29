#include "to_sge_pos.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>

sge::projectile::vector2 const
sanguis::server::collision::to_sge_pos(
	server::pos const &_pos
)
{
	return
		fcppt::math::vector::structure_cast<
			sge::projectile::vector2
		>(
			_pos
		);
}
