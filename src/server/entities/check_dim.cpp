#include <sanguis/pixels_per_meter.hpp>
#include <sanguis/collision/scale.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <sanguis/server/dim.hpp>
#include <sanguis/server/log.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/entities/check_dim.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/math/dim/arithmetic.hpp>


namespace
{

sanguis::server::space_unit const max_side_length(
	fcppt::cast::int_to_float<
		sanguis::server::space_unit
	>(
		sanguis::creator::tile_size::value
	)
	/
	fcppt::cast::int_to_float<
		sanguis::server::space_unit
	>(
		sanguis::pixels_per_meter()
	)
	/
	fcppt::literal<
		sanguis::server::space_unit
	>(
		1.2
	)
);

void
check_size(
	sanguis::server::space_unit const _value
)
{
	if(
		_value > max_side_length
	)
		FCPPT_LOG_WARNING(
			sanguis::server::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Side length ")
				<< _value
				<< FCPPT_TEXT(" for an entity is too large!")
		);
}

}

sanguis::server::dim const
sanguis::server::entities::check_dim(
	sanguis::server::dim const _dim
)
{
	sanguis::server::dim const scaled(
		_dim
		/
		sanguis::collision::scale()
	);

	check_size(
		scaled.w()
	);

	check_size(
		scaled.h()
	);

	return
		scaled;
}
