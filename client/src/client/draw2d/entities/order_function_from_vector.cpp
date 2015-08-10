#include <sanguis/client/draw2d/z_ordering_vector.hpp>
#include <sanguis/client/draw2d/entities/order_function.hpp>
#include <sanguis/client/draw2d/entities/order_function_from_vector.hpp>
#include <sanguis/client/draw2d/sprite/index.hpp>
#include <fcppt/from_optional.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/container/at_optional.hpp>
#include <fcppt/container/maybe_back.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::entities::order_function
sanguis::client::draw2d::entities::order_function_from_vector(
	sanguis::client::draw2d::z_ordering_vector &&_orders
)
{
	// TODO: Use capture by move
	sanguis::client::draw2d::z_ordering_vector const orders(
		std::move(
			_orders
		)
	);

	return
		sanguis::client::draw2d::entities::order_function{
			[
				orders
			](
				sanguis::client::draw2d::sprite::index const _index
			)
			{
				return
					fcppt::from_optional(
						fcppt::container::at_optional(
							orders,
							_index.get()
						),
						[
							orders
						]{
							// TODO: error message
							return
								FCPPT_ASSERT_OPTIONAL_ERROR(
									fcppt::container::maybe_back(
										orders
									)
								);
						}
					);
			}
		};
}
