#include "with_dim.hpp"
#include "radius.hpp"
#include "pos.hpp"
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
	server::dim const &_dim
)
:
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

sge::projectile::shape::shared_base_ptr const
sanguis::server::entities::with_dim::recreate_shape()
{
	return
		collision::create_circle(
			entities::radius(
				this->dim()
			)
		);
}
