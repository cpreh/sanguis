#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/constant_order.hpp>
#include <sanguis/client/draw2d/entities/order_function.hpp>
#include <sanguis/client/draw2d/sprite/index.hpp>


sanguis::client::draw2d::entities::order_function
sanguis::client::draw2d::entities::constant_order(
	sanguis::client::draw2d::z_ordering const _z_ordering
)
{
	return
		sanguis::client::draw2d::entities::order_function{
			[
				_z_ordering
			](
				sanguis::client::draw2d::sprite::index
			)
			{
				return
					_z_ordering;
			}
		};
}
