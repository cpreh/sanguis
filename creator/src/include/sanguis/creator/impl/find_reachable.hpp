#ifndef SANGUIS_CREATOR_IMPL_FIND_REACHABLE_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_FIND_REACHABLE_HPP_INCLUDED

#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/impl/reachable_grid.hpp>


namespace sanguis
{
namespace creator
{
namespace impl
{

sanguis::creator::impl::reachable_grid
find_reachable(
	sanguis::creator::grid const &,
	sanguis::creator::pos const
);

}
}
}

#endif
