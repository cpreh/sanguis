#include <sanguis/collision/world/parameters.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <fcppt/reference_impl.hpp>

sanguis::collision::world::parameters::parameters(
    fcppt::reference<sanguis::creator::grid const> const _grid)
    : grid_(_grid)
{
}

sanguis::creator::grid const &sanguis::collision::world::parameters::grid() const
{
  return grid_.get();
}
