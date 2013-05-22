#include <sanguis/pixels_per_meter.hpp>
#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/client/draw2d/translate/pixels_per_meter.hpp>


sanguis::client::draw2d::funit
sanguis::client::draw2d::translate::pixels_per_meter()
{
	return
		static_cast<
			sanguis::client::draw2d::funit
		>(
			sanguis::pixels_per_meter()
		);
}
