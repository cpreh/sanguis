#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_PROJECTILE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_PROJECTILE_HPP_INCLUDED

#include <sanguis/projectile_type.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/player_id_fwd.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/entities/movement_speed_fwd.hpp>
#include <sanguis/server/entities/projectiles/base.hpp>
#include <sanguis/server/entities/projectiles/life_time.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::server::entities::projectiles
{

class projectile : public sanguis::server::entities::projectiles::base
{
  FCPPT_NONMOVABLE(projectile);

protected:
  projectile(
      sanguis::projectile_type,
      sanguis::server::team,
      sanguis::server::entities::movement_speed,
      sanguis::server::environment::load_context &, // NOLINT(google-runtime-references)
      sanguis::server::entities::projectiles::life_time,
      sanguis::server::direction);

  ~projectile() override;

  [[nodiscard]] sanguis::messages::server::unique_ptr
      add_message(sanguis::server::player_id, sanguis::collision::world::created) const override;

private:
  sanguis::projectile_type const projectile_type_;
};

}

#endif
