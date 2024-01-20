#ifndef SANGUIS_SERVER_WEAPONS_ROCKET_LAUNCHER_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_ROCKET_LAUNCHER_PARAMETERS_HPP_INCLUDED

#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/aoe.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/rocket_launcher_parameters_fwd.hpp> // IWYU pragma: keep
#include <sanguis/server/weapons/attributes/aoe.hpp>
#include <sanguis/server/weapons/attributes/damage.hpp>

namespace sanguis::server::weapons
{

class rocket_launcher_parameters
{
public:
  rocket_launcher_parameters(
      sanguis::server::weapons::damage,
      sanguis::server::weapons::aoe,
      sanguis::server::weapons::accuracy,
      sanguis::server::weapons::backswing_time,
      sanguis::server::weapons::cast_point,
      sanguis::server::weapons::magazine_size,
      sanguis::server::weapons::reload_time,
      sanguis::server::weapons::range);

  [[nodiscard]] sanguis::server::weapons::attributes::damage damage() const;

  [[nodiscard]] sanguis::server::weapons::attributes::aoe aoe() const;

  [[nodiscard]] sanguis::server::weapons::accuracy accuracy() const;

  [[nodiscard]] sanguis::server::weapons::backswing_time backswing_time() const;

  [[nodiscard]] sanguis::server::weapons::cast_point cast_point() const;

  [[nodiscard]] sanguis::server::weapons::magazine_size magazine_size() const;

  [[nodiscard]] sanguis::server::weapons::reload_time reload_time() const;

  [[nodiscard]] sanguis::server::weapons::range range() const;

  void extra_damage(sanguis::server::weapons::damage);

  void extra_aoe(sanguis::server::weapons::aoe);

private:
  sanguis::server::weapons::attributes::damage damage_;

  sanguis::server::weapons::attributes::aoe aoe_;

  sanguis::server::weapons::accuracy accuracy_;

  sanguis::server::weapons::backswing_time backswing_time_;

  sanguis::server::weapons::cast_point cast_point_;

  sanguis::server::weapons::magazine_size magazine_size_;

  sanguis::server::weapons::reload_time reload_time_;

  sanguis::server::weapons::range range_;
};

}

#endif
