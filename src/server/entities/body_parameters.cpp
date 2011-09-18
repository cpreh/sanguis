#include <sanguis/server/entities/body_parameters.hpp>

sanguis::server::entities::body_parameters::body_parameters(
	sge::projectile::shape::shared_base_ptr const _shape,
	collision::solidity const &_solidity
)
:
	shape_(_shape),
	solidity_(_solidity)
{
}

sge::projectile::shape::shared_base_ptr const
sanguis::server::entities::body_parameters::shape() const
{
	return shape_;
}

sanguis::server::collision::solidity const &
sanguis::server::entities::body_parameters::solidity() const
{
	return solidity_;
}
