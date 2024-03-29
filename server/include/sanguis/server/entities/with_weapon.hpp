#ifndef SANGUIS_SERVER_ENTITIES_WITH_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_WEAPON_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/is_primary_weapon_fwd.hpp>
#include <sanguis/magazine_remaining.hpp>
#include <sanguis/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/server/damage/basic_array.hpp>
#include <sanguis/server/damage/type_fwd.hpp>
#include <sanguis/server/damage/unit_fwd.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/ifaces/with_angle.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <sanguis/server/entities/ifaces/with_links.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/entities/ifaces/with_weapon.hpp>
#include <sanguis/server/entities/property/always_max.hpp>
#include <sanguis/server/weapons/const_optional_ref_fwd.hpp>
#include <sanguis/server/weapons/ias.hpp>
#include <sanguis/server/weapons/irs.hpp>
#include <sanguis/server/weapons/optional_target.hpp>
#include <sanguis/server/weapons/optional_unique_ptr.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/optional/reference_fwd.hpp>

namespace sanguis::server::entities
{

class with_weapon : public virtual sanguis::server::entities::base,
                    public virtual sanguis::server::entities::ifaces::with_angle,
                    public virtual sanguis::server::entities::ifaces::with_id,
                    public virtual sanguis::server::entities::ifaces::with_links,
                    public virtual sanguis::server::entities::ifaces::with_weapon,
                    public virtual sanguis::server::entities::ifaces::with_team
{
  FCPPT_NONMOVABLE(with_weapon);

protected:
  with_weapon(
      sanguis::server::weapons::optional_unique_ptr &&,
      sanguis::server::weapons::ias,
      sanguis::server::weapons::irs);

  void update() override;

  void tick(sanguis::duration const &) override;

  [[nodiscard]] sanguis::optional_primary_weapon_type primary_weapon_type() const;

public:
  ~with_weapon() override;

  void pickup_weapon(sanguis::server::weapons::unique_ptr &&);

  [[nodiscard]] sanguis::server::weapons::optional_unique_ptr
      drop_weapon(sanguis::is_primary_weapon);

  void target(sanguis::server::weapons::optional_target);

  [[nodiscard]] sanguis::server::weapons::optional_target target() const;

  [[nodiscard]] bool in_range(sanguis::is_primary_weapon) const;

  void use_weapon(bool, sanguis::is_primary_weapon);

  void reload(sanguis::is_primary_weapon);

  [[nodiscard]] sanguis::server::entities::property::always_max &attack_speed() override;

  [[nodiscard]] sanguis::server::entities::property::always_max &reload_speed() override;

  [[nodiscard]] sanguis::server::entities::property::always_max &
      extra_damage(sanguis::server::damage::type) override;

  [[nodiscard]] sanguis::server::damage::unit
      extra_damage_value(sanguis::server::damage::type) const override;

  [[nodiscard]] sanguis::server::weapons::ias ias() const;

  [[nodiscard]] sanguis::server::weapons::irs irs() const;

  [[nodiscard]] sanguis::server::weapons::const_optional_ref primary_weapon() const;

  [[nodiscard]] sanguis::server::weapons::const_optional_ref secondary_weapon() const;

  void weapon_status(sanguis::weapon_status, sanguis::server::weapons::weapon const &);

  void reload_time(sanguis::duration, sanguis::server::weapons::weapon const &);

  void magazine_remaining(sanguis::magazine_remaining, sanguis::server::weapons::weapon const &);

  [[nodiscard]] sanguis::weapon_status weapon_status() const;

private:
  using optional_weapon_ref = fcppt::optional::reference<sanguis::server::weapons::weapon>;

  [[nodiscard]] sanguis::server::entities::with_weapon::optional_weapon_ref
  primary_weapon_ref() const;

  [[nodiscard]] sanguis::server::entities::with_weapon::optional_weapon_ref
  secondary_weapon_ref() const;

  [[nodiscard]] sanguis::server::entities::with_weapon::optional_weapon_ref
      get_weapon(sanguis::is_primary_weapon) const;

  [[nodiscard]] sanguis::server::weapons::optional_unique_ptr
      move_weapon(sanguis::is_primary_weapon);

  [[nodiscard]] sanguis::server::weapons::weapon &
  set_weapon(sanguis::is_primary_weapon, sanguis::server::weapons::unique_ptr &&);

  static void update_weapon(sanguis::server::entities::with_weapon::optional_weapon_ref const &);

  static void tick_weapon(
      sanguis::duration const &,
      sanguis::server::entities::with_weapon::optional_weapon_ref const &);

  void weapon_changed(sanguis::is_primary_weapon);

  virtual void on_new_weapon(sanguis::server::weapons::weapon const &);

  virtual void on_drop_weapon(sanguis::is_primary_weapon);

  virtual void on_magazine_remaining(sanguis::is_primary_weapon, sanguis::magazine_remaining);

  virtual void on_reload_time(sanguis::is_primary_weapon, sanguis::duration);

  sanguis::server::weapons::optional_unique_ptr primary_weapon_;

  sanguis::server::weapons::optional_unique_ptr secondary_weapon_;

  sanguis::server::weapons::optional_target target_;

  sanguis::weapon_status weapon_status_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)

  sanguis::server::entities::property::always_max attack_speed_;

  sanguis::server::entities::property::always_max reload_speed_;

  using extra_damage_array =
      sanguis::server::damage::basic_array<sanguis::server::entities::property::always_max>;

  extra_damage_array extra_damages_;
};

}

#endif
