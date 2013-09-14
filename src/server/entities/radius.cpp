#include <sanguis/server/dim.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/entities/radius.hpp>
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
		fcppt::literal<
			sanguis::server::space_unit
		>(
			4
		);
}

}

sanguis::server::radius const
sanguis::server::entities::radius(
	sanguis::server::dim const &_dim
)
{
	return
		sanguis::server::radius(
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
