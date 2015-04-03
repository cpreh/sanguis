#ifndef SANGUIS_CREATOR_IMPL_GENERATE_MAZE_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_GENERATE_MAZE_HPP_INCLUDED

#include <sanguis/creator/dim_fwd.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/tile_fwd.hpp>
#include <sanguis/creator/impl/random/generator_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace impl
{

// TODO: Proper types
sanguis::creator::grid
generate_maze(
	sanguis::creator::dim const &,
	unsigned,
	unsigned,
	sanguis::creator::tile,
	sanguis::creator::tile,
	sanguis::creator::impl::random::generator &
);

}
}
}

#endif
