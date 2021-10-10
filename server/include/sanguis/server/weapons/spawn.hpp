#ifndef SANGUIS_SERVER_WEAPONS_SPAWN_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_SPAWN_HPP_INCLUDED

#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/weapon_type_fwd.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/optional_base_ref_fwd.hpp>
#include <sanguis/server/weapons/attack_fwd.hpp>
#include <sanguis/server/weapons/attack_result_fwd.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/common_parameters_fwd.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/spawn_parameters_fwd.hpp>
#include <sanguis/server/weapons/spawn_weapon.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::server::weapons
{

class spawn : public sanguis::server::weapons::weapon
{
  FCPPT_NONMOVABLE(spawn);

public:
  spawn(
      sanguis::server::weapons::common_parameters const &,
      sanguis::weapon_type,
      sanguis::server::weapons::spawn_weapon &&,
      sanguis::server::weapons::range,
      sanguis::server::weapons::backswing_time,
      sanguis::server::weapons::cast_point,
      sanguis::server::weapons::reload_time);

  ~spawn() override;

protected:
  explicit spawn(sanguis::server::weapons::spawn_parameters const &);

  [[nodiscard]] sanguis::server::weapons::spawn_parameters spawn_parameters() const;

private:
  [[nodiscard]] sanguis::server::weapons::attack_result
  do_attack(sanguis::server::weapons::attack const &) override;

  [[nodiscard]] virtual sanguis::server::entities::optional_base_ref do_spawn(
      sanguis::server::weapons::attack const &, sanguis::server::weapons::spawn_weapon const &) = 0;

  [[nodiscard]] sanguis::weapon_attribute_vector attributes() const override;

  void owner_lost() override;

  void kill_spawned();

  [[nodiscard]] virtual sanguis::weapon_attribute_vector extra_attributes() const = 0;

  sanguis::server::weapons::spawn_weapon const spawn_weapon_;

  sanguis::weapon_attribute_vector const attributes_;

  sanguis::server::entities::auto_weak_link spawned_;
};

}

#endif
