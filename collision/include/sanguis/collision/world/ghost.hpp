#ifndef SANGUIS_COLLISION_WORLD_GHOST_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_GHOST_HPP_INCLUDED

#include <sanguis/collision/center_fwd.hpp>
#include <sanguis/collision/world/ghost_fwd.hpp> // IWYU pragma: keep
#include <fcppt/nonmovable.hpp>

namespace sanguis::collision::world
{

class ghost
{
  FCPPT_NONMOVABLE(ghost);

protected:
  ghost();

public:
  virtual ~ghost();

  virtual void center(sanguis::collision::center) = 0;
};

}

#endif
