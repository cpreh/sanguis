#include <sanguis/server/collision/from_sge_vector.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>

sanguis::server::vector const
sanguis::server::collision::from_sge_vector(
	sge::projectile::vector2 const &_vector
)
{
	return
		fcppt::math::vector::structure_cast<
			sge::projectile::vector2
		>(
			_vector
		);
}
