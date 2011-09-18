#include <sanguis/server/entities/default_solid.hpp>
#include <sanguis/server/collision/solidity.hpp>
#include <sge/projectile/body/mass.hpp>
#include <sge/projectile/body/solidity/solid.hpp>

sanguis::server::collision::solidity const
sanguis::server::entities::default_solid()
{
	return
		collision::solidity(
			sge::projectile::body::solidity::solid(
				sge::projectile::body::mass(
					1
				)
			)
		);
}
