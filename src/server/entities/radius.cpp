#include <sanguis/server/dim.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/entities/radius.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>

namespace
{

sanguis::server::space_unit
quad_half(
	sanguis::server::space_unit const _val
)
{
	return
		_val
		*
		_val
		/
		static_cast<
			sanguis::server::space_unit
		>(
			4
		);
}

}

sanguis::server::radius const
sanguis::server::entities::radius(
	server::dim const &_dim
)
{
	return
		server::radius(
			std::sqrt(
				quad_half(
					_dim.w()
				)
				+
				quad_half(
					_dim.h()
				)
			)
		);
}
