#include <sanguis/server/collision/solidity.hpp>

sanguis::server::collision::solidity::solidity(
	sge::projectile::body::solidity::variant const &_solidity
)
:
	solidity_(_solidity)
{
}

sge::projectile::body::solidity::variant const &
sanguis::server::collision::solidity::get() const
{
	return solidity_;
}
