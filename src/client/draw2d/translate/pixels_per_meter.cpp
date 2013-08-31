#include <sanguis/pixels_per_meter.hpp>
#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/client/draw2d/translate/pixels_per_meter.hpp>
#include <fcppt/cast/int_to_float.hpp>


sanguis::client::draw2d::funit
sanguis::client::draw2d::translate::pixels_per_meter()
{
	return
		fcppt::cast::int_to_float<
			sanguis::client::draw2d::funit
		>(
			sanguis::pixels_per_meter()
		);
}
