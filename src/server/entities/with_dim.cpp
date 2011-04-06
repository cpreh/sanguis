#include "with_dim.hpp"
#include "body_parameters.hpp"
#include "pos.hpp"
#include "radius.hpp"
#include "../collision/create_circle.hpp"
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

sanguis::server::pos const
sanguis::server::entities::with_dim::pos() const
{
	return
		entities::pos(
			this->center(),
			this->dim()
		);
}

sanguis::server::entities::with_dim::with_dim(
	collision::solidity const &_solidity,
	server::dim const &_dim
)
:
	entities::with_body(
		entities::body_parameters(
			collision::create_circle(
				entities::radius(
					_dim
				)
			),
			_solidity
		)
	),
	dim_(_dim)
{
}

sanguis::server::entities::with_dim::~with_dim()
{
}

sanguis::server::dim const &
sanguis::server::entities::with_dim::dim() const
{
	return dim_;
}
