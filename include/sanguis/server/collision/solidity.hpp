#ifndef SANGUIS_SERVER_COLLISION_SOLIDITY_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_SOLIDITY_HPP_INCLUDED

#include <sanguis/server/collision/solidity_fwd.hpp>
#include <sge/projectile/body/solidity/variant.hpp>


namespace sanguis
{
namespace server
{
namespace collision
{

class solidity
{
public:
	explicit
	solidity(
		sge::projectile::body::solidity::variant const &
	);

	sge::projectile::body::solidity::variant const &
	get() const;
private:
	sge::projectile::body::solidity::variant solidity_;
};

}
}
}

#endif
