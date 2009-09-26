#include "with_dim.hpp"
#include "radius.hpp"
#include "pos.hpp"
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/vector/basic_impl.hpp>

sanguis::server::pos_type const
sanguis::server::entities::with_dim::pos() const
{
	return entities::pos(
		center(),
		dim()
	);
}

sanguis::server::entities::with_dim::with_dim(
	dim_type const &dim_
)
:
	dim_(dim_)
{}

sanguis::server::entities::with_dim::~with_dim()
{}

sanguis::server::dim_type const &
sanguis::server::entities::with_dim::dim() const
{
	return dim_;
}

sanguis::server::space_unit
sanguis::server::entities::with_dim::radius() const
{
	return entities::radius(
		dim()
	);
}
