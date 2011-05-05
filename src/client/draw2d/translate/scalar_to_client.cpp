#include "scalar_to_client.hpp"
#include "pixels_per_meter.hpp"

sanguis::client::draw2d::funit
sanguis::client::draw2d::translate::scalar_to_client(
	messages::types::space_unit const _scalar
)
{
	return
		static_cast<
			draw2d::funit
		>(
			_scalar
		)
		*
		translate::pixels_per_meter();
}
