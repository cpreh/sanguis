#ifndef SANGUIS_SERVER_AURAS_TARGET_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_TARGET_HPP_INCLUDED

#include <sanguis/optional_aura_type_fwd.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/server/add_target_callback.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/remove_target_callback.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/target_kind_fwd.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <sanguis/server/entities/with_body_ref.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::server::auras
{

class target : public sanguis::server::auras::aura
{
  FCPPT_NONMOVABLE(target);

public:
  target(
      sanguis::server::radius,
      sanguis::server::team,
      sanguis::server::auras::target_kind,
      sanguis::server::add_target_callback &&,
      sanguis::server::remove_target_callback &&);

  ~target() override;

private:
  [[nodiscard]] sanguis::optional_aura_type type() const override;

  void enter(sanguis::server::entities::with_body_ref, sanguis::collision::world::created) override;

  void leave(sanguis::server::entities::with_body & // NOLINT(google-runtime-references)
             ) override;

  sanguis::server::add_target_callback const add_target_;

  sanguis::server::remove_target_callback const remove_target_;
};

}

#endif
