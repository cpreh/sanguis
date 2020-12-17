#ifndef SANGUIS_TILES_CELL_CONTAINER_HPP_INCLUDED
#define SANGUIS_TILES_CELL_CONTAINER_HPP_INCLUDED

#include <sanguis/tiles/cell.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tiles
{

using
cell_container
=
std::vector<
	sanguis::tiles::cell
>;

}
}

#endif
