#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/impl/make_spiral_range.hpp>
#include <sanguis/creator/difference_type.hpp>
#include <sanguis/creator/grid_spiral_range.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <fcppt/boost_units_value.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/cast/float_to_int_fun.hpp>
#include <fcppt/container/grid/make_spiral_range.hpp>
#include <fcppt/math/ceil_div_signed.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/map.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional/object_impl.hpp>


sanguis::creator::grid_spiral_range
sanguis::collision::impl::make_spiral_range(
	sanguis::collision::center const _center,
	sanguis::collision::radius const _radius
)
{
	sanguis::creator::difference_type const tile_size(
		fcppt::cast::to_signed(
			sanguis::creator::tile_size::value
		)
	);

	fcppt::optional::object<
		sanguis::creator::signed_pos
	> const optional_pos{
		fcppt::math::vector::structure_cast<
			sanguis::creator::signed_pos,
			fcppt::cast::float_to_int_fun
		>(
			fcppt::math::vector::map(
				_center.get(),
				fcppt::boost_units_value{}
			)
		)
		/
		tile_size
	};

	return
		fcppt::container::grid::make_spiral_range(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				optional_pos
			),
			fcppt::literal<
				sanguis::creator::difference_type
			>(
				4 // TODO: Why?
			)
			*
			FCPPT_ASSERT_OPTIONAL_ERROR(
				fcppt::math::ceil_div_signed(
					fcppt::cast::float_to_int<
						sanguis::creator::difference_type
					>(
						_radius.get().value()
					),
					tile_size
				)
			)
		);
}
