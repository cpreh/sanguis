#include "pos.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/arithmetic.hpp>

sanguis::server::pos_type const
sanguis::server::entities::pos(
	pos_type const &center_,
	dim_type const &dim_
)
{
	return center_ - dim_ / static_cast<space_unit>(2);
}
