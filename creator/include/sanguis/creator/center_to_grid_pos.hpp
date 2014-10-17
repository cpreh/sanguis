#ifndef SANGUIS_CREATOR_CENTER_TO_GRID_POS_HPP_INCLUDED
#define SANGUIS_CREATOR_CENTER_TO_GRID_POS_HPP_INCLUDED

#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


namespace sanguis
{
namespace creator
{

template<
	typename Unit
>
inline
sanguis::creator::pos const
center_to_grid_pos(
	fcppt::math::vector::static_<
		Unit,
		2
	> const _center
)
{
	return
		fcppt::math::vector::structure_cast<
			sanguis::creator::pos
		>(
			_center
		)
		/
		sanguis::creator::tile_size::value;
}

}
}

#endif
