#ifndef SANGUIS_TILES_POS_FWD_HPP_INCLUDED
#define SANGUIS_TILES_POS_FWD_HPP_INCLUDED

#include <sanguis/tiles/unit.hpp>
#include <fcppt/math/vector/static_fwd.hpp>


namespace sanguis::tiles
{

using
pos
=
fcppt::math::vector::static_<
	sanguis::tiles::unit,
	2
>;

}

#endif
