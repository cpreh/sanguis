#include <sanguis/server/collision/solidity.hpp>
#include <sanguis/server/entities/nonsolid.hpp>
#include <sge/projectile/body/solidity/nonsolid.hpp>


sanguis::server::collision::solidity const
sanguis::server::entities::nonsolid()
{
	return
		sanguis::server::collision::solidity(
			sge::projectile::body::solidity::nonsolid()
		);
}
