#include <sanguis/server/entities/nonsolid.hpp>
#include <sge/projectile/body/solidity/nonsolid.hpp>

sanguis::server::collision::solidity const
sanguis::server::entities::nonsolid()
{
	return
		collision::solidity(
			sge::projectile::body::solidity::nonsolid()
		);
}
