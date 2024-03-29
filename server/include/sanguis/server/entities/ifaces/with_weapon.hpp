#ifndef SANGUIS_SERVER_ENTITIES_IFACES_WITH_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_IFACES_WITH_WEAPON_HPP_INCLUDED

#include <sanguis/server/damage/type_fwd.hpp>
#include <sanguis/server/damage/unit_fwd.hpp>
#include <sanguis/server/entities/ifaces/with_weapon_fwd.hpp>
#include <sanguis/server/entities/property/always_max_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::server::entities::ifaces
{

class with_weapon
{
  FCPPT_NONMOVABLE(with_weapon);

protected:
  with_weapon();

public:
  virtual ~with_weapon();

  [[nodiscard]] virtual sanguis::server::entities::property::always_max &attack_speed() = 0;

  [[nodiscard]] virtual sanguis::server::entities::property::always_max &reload_speed() = 0;

  [[nodiscard]] virtual sanguis::server::entities::property::always_max &
      extra_damage(sanguis::server::damage::type) = 0;

  [[nodiscard]] virtual sanguis::server::damage::unit
      extra_damage_value(sanguis::server::damage::type) const = 0;
};

}

#endif
