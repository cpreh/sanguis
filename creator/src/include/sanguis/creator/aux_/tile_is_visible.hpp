#ifndef SANGUIS_CREATOR_AUX__TILE_IS_VISIBLE_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__TILE_IS_VISIBLE_HPP_INCLUDED

#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/creator/grid_fwd.hpp>

namespace sanguis
{
namespace creator
{
namespace aux_
{

bool
tile_is_visible(
	sanguis::creator::grid const &,
	sanguis::creator::pos const &,
	sanguis::creator::pos const &
);

}
}
}

#endif
