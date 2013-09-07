#include <sanguis/collision/dim2.hpp>
#include <sanguis/collision/aux/world/projectile/to_sge_dim.hpp>
#include <sge/projectile/dim2.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sge::projectile::dim2 const
sanguis::collision::aux::world::projectile::to_sge_dim(
	sanguis::collision::dim2 const &_dim
)
{
	return
		fcppt::math::dim::structure_cast<
			sge::projectile::dim2
		>(
			_dim
		);
}
