#ifndef SANGUIS_CREATOR_TILE_IS_VISIBLE_HPP_INCLUDED
#define SANGUIS_CREATOR_TILE_IS_VISIBLE_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/creator/symbol.hpp>


namespace sanguis
{
namespace creator
{

SANGUIS_CREATOR_SYMBOL
bool
tile_is_visible(
	sanguis::creator::grid const &,
	sanguis::creator::pos const &,
	sanguis::creator::pos const &
);

}
}

#endif
