#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/speed_is_null.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/length.hpp>


bool
sanguis::client::draw2d::speed_is_null(
	draw2d::speed const &_speed
)
{
	return
		fcppt::math::vector::length(
			_speed.get()
		)
		<
		static_cast<
			draw2d::funit
		>(
			0.0001f
		);
}
