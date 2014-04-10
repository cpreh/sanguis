#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/model/expand_orders.hpp>
#include <sanguis/client/load/model/part_map.hpp>
#include <fcppt/assert/pre.hpp>


sanguis::client::draw2d::entities::order_vector
sanguis::client::draw2d::entities::model::expand_orders(
	sanguis::client::draw2d::entities::order_vector _orders,
	sanguis::client::load::model::part_map::size_type const _size
)
{
	FCPPT_ASSERT_PRE(
		!_orders.empty()
	);

	FCPPT_ASSERT_PRE(
		_orders.size()
		<=
		_size
	);

	_orders.resize(
		_size,
		_orders.back()
	);

	return
		_orders;
}
