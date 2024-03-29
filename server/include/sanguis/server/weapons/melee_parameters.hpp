#ifndef SANGUIS_SERVER_WEAPONS_MELEE_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MELEE_PARAMETERS_HPP_INCLUDED

#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/melee_parameters_fwd.hpp> // IWYU pragma: keep
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/attributes/damage.hpp>

namespace sanguis::server::weapons
{

class melee_parameters
{
public:
  melee_parameters(
      sanguis::server::weapons::range,
      sanguis::server::weapons::backswing_time,
      sanguis::server::weapons::damage,
      sanguis::server::damage::array const &);

  [[nodiscard]] sanguis::server::weapons::backswing_time backswing_time() const;

  [[nodiscard]] sanguis::server::weapons::attributes::damage damage() const;

  [[nodiscard]] sanguis::server::weapons::range range() const;

  [[nodiscard]] sanguis::server::damage::array const &damage_values() const;

  void extra_damage(sanguis::server::weapons::damage);

private:
  sanguis::server::weapons::range range_;

  sanguis::server::weapons::backswing_time backswing_time_;

  sanguis::server::weapons::attributes::damage damage_;

  sanguis::server::damage::array damage_values_;
};

}

#endif
