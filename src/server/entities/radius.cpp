#include "radius.hpp"
#include <fcppt/math/quad.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <cmath>

sanguis::server::space_unit
sanguis::server::entities::radius(
	server::dim const &_dim
)
{
	return
		std::sqrt(
			fcppt::math::quad(
				_dim.w() / 2
			)
			+
			fcppt::math::quad(
				_dim.h() / 2
			)
		);
}
