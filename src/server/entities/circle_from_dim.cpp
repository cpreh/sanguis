#include "circle_from_dim.hpp"
#include "body_parameters.hpp"
#include "radius.hpp"
#include "../collision/create_circle.hpp"

sanguis::server::entities::body_parameters const
sanguis::server::entities::circle_from_dim(
	server::dim const &_dim,
	collision::solidity const &_solidity
)
{
	return
		entities::body_parameters(
			collision::create_circle(
				entities::radius(
					_dim
				)
			),
			_solidity
		);
}
