#include <sanguis/server/entities/radius.hpp>
#include <fcppt/math/quad.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>

sanguis::server::radius const
sanguis::server::entities::radius(
	server::dim const &_dim
)
{
	return
		server::radius(
			std::sqrt(
				fcppt::math::quad(
					_dim.w() / 2
				)
				+
				fcppt::math::quad(
					_dim.h() / 2
				)
			)
		);
}
