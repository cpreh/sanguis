#ifndef SANGUIS_CREATOR_IMPL_GENERATE_MAZE_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_GENERATE_MAZE_HPP_INCLUDED

#include <sanguis/creator/impl/maze_result.hpp>
#include <sanguis/creator/impl/reachable_grid.hpp>
#include <sanguis/creator/impl/random/generator_fwd.hpp>
#include <fcppt/reference_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace impl
{

[[nodiscard]]
sanguis::creator::impl::maze_result
generate_maze(
	fcppt::reference<
		sanguis::creator::impl::reachable_grid
	>,
	sanguis::creator::impl::random::generator & // NOLINT(google-runtime-references)
); // NOLINT(google-runtime-references)

}
}
}

#endif
