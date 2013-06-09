#include <sanguis/server/radius.hpp>
#include <sanguis/server/collision/solidity.hpp>
#include <sanguis/server/entities/body_parameters.hpp>


sanguis::server::entities::body_parameters::body_parameters(
	sanguis::server::radius const _radius,
	sanguis::server::collision::solidity const &_solidity
)
:
	radius_(
		_radius
	),
	solidity_(
		_solidity
	)
{
}

sanguis::server::radius const
sanguis::server::entities::body_parameters::radius() const
{
	return radius_;
}

sanguis::server::collision::solidity const &
sanguis::server::entities::body_parameters::solidity() const
{
	return solidity_;
}
