#ifndef SANGUIS_CREATOR_IMPL_INTERIOR_RANGE_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_INTERIOR_RANGE_HPP_INCLUDED

#include <sanguis/creator/dim.hpp>
#include <sanguis/creator/min.hpp>
#include <sanguis/creator/sup.hpp>
#include <fcppt/container/grid/make_pos_ref_range_start_end.hpp>
#include <fcppt/container/grid/pos_ref_range_impl.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/dim/to_vector.hpp>
#include <fcppt/math/vector/fill.hpp>


namespace sanguis
{
namespace creator
{
namespace impl
{

template<
	typename Grid
>
fcppt::container::grid::pos_ref_range<
	Grid
>
interior_range(
	Grid &_grid
)
{
	return
		fcppt::container::grid::make_pos_ref_range_start_end(
			_grid,
			sanguis::creator::min{
				fcppt::math::vector::fill<
					sanguis::creator::pos
				>(
					1
				)
			},
			sanguis::creator::sup{
				fcppt::math::dim::to_vector(
					_grid.size()
					-
					fcppt::math::dim::fill<
						sanguis::creator::dim
					>(
						1u
					)
				)
			}
		);
}

}
}
}

#endif
