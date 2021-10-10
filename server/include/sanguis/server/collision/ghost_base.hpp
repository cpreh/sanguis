#ifndef SANGUIS_SERVER_COLLISION_GHOST_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_GHOST_BASE_HPP_INCLUDED

#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_base_ref.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/collision/world/ghost_base.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool_fwd.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::collision
{

class ghost_base : public sanguis::collision::world::ghost_base
{
  FCPPT_NONMOVABLE(ghost_base);

protected:
  ghost_base();

  ~ghost_base() override;

public:
  void body_enter(sanguis::collision::world::body_base_ref, sanguis::collision::world::created);

  void body_exit(sanguis::collision::world::body_base & // NOLINT)google-runtime-references)
  ); // NOLINT(google-runtime-references)
private:
  virtual void on_body_enter(
      sanguis::collision::world::body_base_ref, sanguis::collision::world::created) = 0;

  virtual void
  on_body_exit(sanguis::collision::world::body_base & // NOLINT(google-runtime-references)
               ) = 0; // NOLINT(google-runtime-references)

  [[nodiscard]] virtual boost::logic::tribool
  can_collide_with(sanguis::collision::world::body_base const &) const = 0;
};

}

#endif
