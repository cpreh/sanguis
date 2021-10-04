#ifndef SANGUIS_CREATOR_IMPL_SET_OPENING_TILES_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_SET_OPENING_TILES_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/opening_container_array_fwd.hpp>
#include <fcppt/reference_fwd.hpp>


namespace sanguis::creator::impl
{

void
set_opening_tiles(
	fcppt::reference<
		sanguis::creator::grid
	>,
	sanguis::creator::opening_container_array const &
);

}

#endif
