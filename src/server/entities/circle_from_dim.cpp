#include <sanguis/server/dim_fwd.hpp>
#include <sanguis/server/entities/circle_from_dim.hpp>
#include <sanguis/server/entities/body_parameters.hpp>
#include <sanguis/server/entities/radius.hpp>
#include <sanguis/server/collision/create_circle.hpp>
#include <sanguis/server/collision/solidity_fwd.hpp>


sanguis::server::entities::body_parameters const
sanguis::server::entities::circle_from_dim(
	sanguis::server::dim const &_dim,
	sanguis::server::collision::solidity const &_solidity
)
{
	return
		sanguis::server::entities::body_parameters(
			sanguis::server::collision::create_circle(
				sanguis::server::entities::radius(
					_dim
				)
			),
			_solidity
		);
}
