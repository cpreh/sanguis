#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/client/draw2d/translate/scalar_to_client.hpp>
#include <sanguis/client/draw2d/translate/pixels_per_meter.hpp>
#include <sanguis/messages/types/space_unit.hpp>
#include <fcppt/cast/size.hpp>


sanguis::client::draw2d::funit
sanguis::client::draw2d::translate::scalar_to_client(
	sanguis::messages::types::space_unit const _scalar
)
{
	return
		fcppt::cast::size<
			sanguis::client::draw2d::funit
		>(
			_scalar
		)
		*
		sanguis::client::draw2d::translate::pixels_per_meter();
}
