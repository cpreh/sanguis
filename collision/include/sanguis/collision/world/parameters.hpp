#ifndef SANGUIS_COLLISION_WORLD_PARAMETERS_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_PARAMETERS_HPP_INCLUDED

#include <sanguis/collision/symbol.hpp>
#include <sanguis/collision/world/parameters_fwd.hpp> // IWYU pragma: keep
#include <sanguis/creator/grid_fwd.hpp>
#include <fcppt/reference_impl.hpp>

namespace sanguis::collision::world
{

class parameters
{
public:
  SANGUIS_COLLISION_SYMBOL
  explicit parameters(fcppt::reference<sanguis::creator::grid const>);

  [[nodiscard]] sanguis::creator::grid const &grid() const;

private:
  fcppt::reference<sanguis::creator::grid const> grid_;
};

}

#endif
