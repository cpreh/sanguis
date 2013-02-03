#include <sanguis/server/dim.hpp>
#include <sanguis/server/collision/to_sge_dim.hpp>
#include <sge/projectile/dim2.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sge::projectile::dim2 const
sanguis::server::collision::to_sge_dim(
	sanguis::server::dim const &_dim
)
{
	return
		fcppt::math::dim::structure_cast<
			sge::projectile::dim2
		>(
			_dim
		);
}
