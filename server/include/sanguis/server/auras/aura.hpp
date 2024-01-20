#ifndef SANGUIS_SERVER_AURAS_AURA_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_AURA_HPP_INCLUDED

#include <sanguis/optional_aura_type_fwd.hpp>
#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_base_ref.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/collision/world/ghost_group_fwd.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/auras/aura_fwd.hpp> // IWYU pragma: keep
#include <sanguis/server/collision/ghost.hpp>
#include <sanguis/server/collision/ghost_base.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <sanguis/server/entities/with_body_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool_fwd.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::auras
{

class aura : private sanguis::server::collision::ghost_base
{
  FCPPT_NONMOVABLE(aura);

public:
  ~aura() override;

  [[nodiscard]] sanguis::server::collision::ghost create_ghost();

  [[nodiscard]] virtual sanguis::optional_aura_type type() const = 0;

protected:
  aura(sanguis::server::radius, sanguis::collision::world::ghost_group);

private:
  [[nodiscard]] boost::logic::tribool
  can_collide_with(sanguis::collision::world::body_base const &) const override;

  void on_body_enter(
      sanguis::collision::world::body_base_ref, sanguis::collision::world::created) override;

  void on_body_exit(sanguis::collision::world::body_base & // NOLINT(google-runtime-references)
                    ) override;

  virtual void
      enter(sanguis::server::entities::with_body_ref, sanguis::collision::world::created) = 0;

  virtual void leave(sanguis::server::entities::with_body & // NOLINT(google-runtime-references)
                     ) = 0; // NOLINT(google-runtime-references)

  sanguis::server::radius const radius_;

  sanguis::collision::world::ghost_group const collision_group_;
};

}

#endif
