#ifndef SANGUIS_COLLISION_WORLD_OBJECT_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_OBJECT_HPP_INCLUDED

#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/collision/world/body_exit_container.hpp>
#include <sanguis/collision/world/body_fwd.hpp>
#include <sanguis/collision/world/body_parameters_fwd.hpp>
#include <sanguis/collision/world/body_unique_ptr.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/collision/world/ghost_fwd.hpp>
#include <sanguis/collision/world/ghost_parameters_fwd.hpp>
#include <sanguis/collision/world/ghost_unique_ptr.hpp>
#include <sanguis/collision/world/object_fwd.hpp> // IWYU pragma: keep
#include <sanguis/collision/world/update_result_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_fwd.hpp>

namespace sanguis::collision::world
{

class object
{
  FCPPT_NONMOVABLE(object);

protected:
  object();

public:
  virtual ~object();

  [[nodiscard]] virtual sanguis::collision::world::body_unique_ptr
  create_body(sanguis::collision::world::body_parameters const &) = 0;

  [[nodiscard]] virtual sanguis::collision::world::body_enter_container activate_body(
      fcppt::reference<sanguis::collision::world::body>, sanguis::collision::world::created) = 0;

  [[nodiscard]] virtual sanguis::collision::world::body_exit_container
      deactivate_body(fcppt::reference<sanguis::collision::world::body>) = 0;

  [[nodiscard]] virtual sanguis::collision::world::ghost_unique_ptr
  create_ghost(sanguis::collision::world::ghost_parameters const &) = 0;

  [[nodiscard]] virtual sanguis::collision::world::body_enter_container
      activate_ghost(fcppt::reference<sanguis::collision::world::ghost>) = 0;

  [[nodiscard]] virtual sanguis::collision::world::body_exit_container
      deactivate_ghost(fcppt::reference<sanguis::collision::world::ghost>) = 0;

  [[nodiscard]] virtual sanguis::collision::world::update_result
      update(sanguis::collision::duration) = 0;
};

}

#endif
