#ifndef SANGUIS_CREATOR_GRID_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_GRID_FWD_HPP_INCLUDED

#include <sanguis/creator/tile_fwd.hpp>
#include <fcppt/container/grid/object_fwd.hpp>


namespace sanguis
{
namespace creator
{

typedef
fcppt::container::grid::object<
	sanguis::creator::tile,
	2u
>
grid;

}
}

#endif
