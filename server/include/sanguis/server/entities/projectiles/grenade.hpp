#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_GRENADE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_GRENADE_HPP_INCLUDED

#include <sanguis/diff_timer.hpp>
#include <sanguis/server/aoe_fwd.hpp>
#include <sanguis/server/direction_fwd.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/vector.hpp>
#include <sanguis/server/damage/modified_array.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/optional_transfer_result_fwd.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/server/entities/projectiles/aoe_projectile.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::server::entities::projectiles
{

class grenade : public sanguis::server::entities::projectiles::aoe_projectile
{
  FCPPT_NONMOVABLE(grenade);

public:
  grenade(
      sanguis::server::environment::load_context &, // NOLINT(google-runtime-references)
      sanguis::server::team,
      sanguis::server::damage::unit,
      sanguis::server::damage::modified_array const &,
      sanguis::server::aoe,
      sanguis::server::vector dest,
      sanguis::server::direction);

  ~grenade() override;

private:
  [[nodiscard]] sanguis::server::entities::optional_transfer_result
  on_transfer(sanguis::server::entities::transfer_parameters const &) override;

  void do_damage(sanguis::server::entities::with_health &) override;

  void update() override;

  void remove_from_game() override;

  sanguis::diff_timer slowdown_timer_;

  sanguis::server::damage::unit const damage_;

  sanguis::server::damage::modified_array const damage_modifiers_;

  sanguis::server::vector const dest_;
};

}

#endif
