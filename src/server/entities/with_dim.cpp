#include "with_dim.hpp"
#include "radius.hpp"
#include "pos.hpp"
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

sanguis::server::pos_type const
sanguis::server::entities::with_dim::pos() const
{
	return
		entities::pos(
			this->center(),
			this->dim()
		);
}

sanguis::server::entities::with_dim::with_dim(
	dim_type const &_dim
)
:
	dim_(_dim)
{
}

sanguis::server::entities::with_dim::~with_dim()
{
}

sanguis::server::dim_type const &
sanguis::server::entities::with_dim::dim() const
{
	return dim_;
}

sanguis::server::space_unit
sanguis::server::entities::with_dim::radius() const
{
	return
		entities::radius(
			this->dim()
		);
}
