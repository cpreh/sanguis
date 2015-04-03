#ifndef SANGUIS_CREATOR_IMPL_REACHABLE_GRID_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_REACHABLE_GRID_HPP_INCLUDED

#include <sanguis/creator/impl/reachable.hpp>
#include <fcppt/container/grid/object.hpp>


namespace sanguis
{
namespace creator
{
namespace impl
{

typedef
fcppt::container::grid::object<
	sanguis::creator::impl::reachable,
	2
>
reachable_grid;

}
}
}

#endif
