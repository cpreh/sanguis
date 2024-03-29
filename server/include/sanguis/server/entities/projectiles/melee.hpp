#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_MELEE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_MELEE_HPP_INCLUDED

#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/damage/modified_array_fwd.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/projectiles/aoe_damage.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::server::entities::projectiles
{

class melee : public sanguis::server::entities::projectiles::aoe_damage
{
  FCPPT_NONMOVABLE(melee);

public:
  melee(
      sanguis::server::team,
      sanguis::server::damage::unit,
      sanguis::server::damage::modified_array const &);

  ~melee() override;
};

}

#endif
