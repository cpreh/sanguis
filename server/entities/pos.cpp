#include "pos.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/dim.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/dim/arithmetic.hpp>

sanguis::server::pos_type const
sanguis::server::entities::pos(
	pos_type const &center_,
	dim_type const &dim_
)
{
	return center_ - dim_ / 2;
}
