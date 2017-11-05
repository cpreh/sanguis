#include <sanguis/collision/center.hpp>
#include <sanguis/collision/length2.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/impl/make_range.hpp>
#include <sanguis/creator/difference_type.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/grid_crange.hpp>
#include <sanguis/creator/min.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <sanguis/creator/sup.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <fcppt/boost_units_value.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/cast/float_to_int_fun.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/container/grid/clamped_min.hpp>
#include <fcppt/container/grid/clamped_sup_signed.hpp>
#include <fcppt/container/grid/make_pos_ref_crange_start_end.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/ceil_div_signed.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/fill.hpp>
#include <fcppt/math/vector/map.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional/object_impl.hpp>


sanguis::creator::grid_crange
sanguis::collision::impl::make_range(
	sanguis::creator::grid const &_grid,
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
				_center.get()
				-
				fcppt::math::vector::fill<
					sanguis::collision::length2
				>(
					_radius.get()
				)
				,
				fcppt::boost_units_value{}
			)
		)
		/
		tile_size
	};

	sanguis::creator::min const lower(
		fcppt::container::grid::clamped_min(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				optional_pos
			)
		)
	);

	sanguis::creator::sup const upper(
		fcppt::container::grid::clamped_sup_signed(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				fcppt::math::vector::ceil_div_signed(
					fcppt::math::vector::structure_cast<
						sanguis::creator::signed_pos,
						fcppt::cast::float_to_int_fun
					>(
						fcppt::math::vector::map(
							_center.get()
							+
							fcppt::math::vector::fill<
								sanguis::collision::length2
							>(
								_radius.get()
							)
							,
							fcppt::boost_units_value{}
						)
					),
					tile_size
				)
			),
			_grid.size()
		)
	);

	return
		fcppt::container::grid::make_pos_ref_crange_start_end(
			_grid,
			lower,
			upper
		);
}
