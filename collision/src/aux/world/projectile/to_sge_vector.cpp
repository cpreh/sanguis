#include <sanguis/collision/vector2.hpp>
#include <sanguis/collision/aux/world/projectile/to_sge_vector.hpp>
#include <sge/projectile/vector2.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sge::projectile::vector2 const
sanguis::collision::aux::world::projectile::to_sge_vector(
	sanguis::collision::vector2 const &_vector
)
{
	return
		fcppt::math::vector::structure_cast<
			sge::projectile::vector2
		>(
			_vector
		);
}
