#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/client/draw2d/translate/scalar_from_client.hpp>
#include <sanguis/client/draw2d/translate/pixels_per_meter.hpp>
#include <sanguis/messages/types/space_unit.hpp>


sanguis::client::draw2d::funit
sanguis::client::draw2d::translate::scalar_from_client(
	sanguis::messages::types::space_unit const _scalar
)
{
	return
		static_cast<
			sanguis::client::draw2d::funit
		>(
			_scalar
		)
		/
		sanguis::client::draw2d::translate::pixels_per_meter();
}
