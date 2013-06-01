#include <sanguis/collision_scale.hpp>
#include <sanguis/pixels_per_meter.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <sanguis/server/dim.hpp>
#include <sanguis/server/log.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/entities/radius.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/math/dim/object_impl.hpp>
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
	sanguis::server::dim const &_dim
)
{
	sanguis::server::radius const result(
		std::sqrt(
			quad_half(
				_dim.w()
			)
			+
			quad_half(
				_dim.h()
			)
		)
		/
		static_cast<
			sanguis::server::space_unit
		>(
			sanguis::collision_scale()
		)
	);

	sanguis::server::space_unit const max_radius(
		static_cast<
			sanguis::server::space_unit
		>(
			sanguis::creator::tile_size::value
		)
		/
		static_cast<
			sanguis::server::space_unit
		>(
			sanguis::pixels_per_meter()
		)
		/
		2.5f
	);

	if(
		result.get() > max_radius
	)
	{
		FCPPT_LOG_WARNING(
			sanguis::server::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Radius ")
				<< result
				<< FCPPT_TEXT(" for an entity is too large, reducing it.")
		);

		return
			sanguis::server::radius(
				max_radius
			);
	}

	return
		result;
}
