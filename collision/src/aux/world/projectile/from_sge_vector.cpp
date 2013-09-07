#include <sanguis/collision/vector2.hpp>
#include <sanguis/collision/aux/world/projectile/from_sge_vector.hpp>
#include <sge/projectile/vector2.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sanguis::collision::vector2 const
sanguis::collision::aux::world::projectile::from_sge_vector(
	sge::projectile::vector2 const &_vector
)
{
	return
		fcppt::math::vector::structure_cast<
			sanguis::collision::vector2
		>(
			_vector
		);
}
