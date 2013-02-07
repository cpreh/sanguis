#include <sanguis/server/vector.hpp>
#include <sanguis/server/collision/to_sge_vector.hpp>
#include <sge/projectile/vector2.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sge::projectile::vector2 const
sanguis::server::collision::to_sge_vector(
	sanguis::server::vector const &_vec
)
{
	return
		fcppt::math::vector::structure_cast<
			sge::projectile::vector2
		>(
			_vec
		);
}
