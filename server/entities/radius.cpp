#include "radius.hpp"
#include <sge/math/quad.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <cmath>

sanguis::server::space_unit
sanguis::server::entities::radius(
	dim_type const &d)
{
	return std::sqrt(
		sge::math::quad(d.w() / 2)
		+ sge::math::quad(d.h() / 2)
	);
}
