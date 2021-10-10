#ifndef SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED

#include <sanguis/diff_clock.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/magazine_remaining.hpp>
#include <sanguis/magazine_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/weapon_description_fwd.hpp>
#include <sanguis/weapon_status_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/entities/optional_with_weapon_ref.hpp>
#include <sanguis/server/entities/with_weapon_fwd.hpp>
#include <sanguis/server/weapons/attack_fwd.hpp>
#include <sanguis/server/weapons/attack_result_fwd.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/log_cref.hpp>
#include <sanguis/server/weapons/log_fwd.hpp>
#include <sanguis/server/weapons/optional_reload_time.hpp>
#include <sanguis/server/weapons/parameters_fwd.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/target_fwd.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon_fwd.hpp>
#include <sanguis/server/weapons/attributes/magazine_size_fwd.hpp>
#include <sanguis/server/weapons/attributes/optional_accuracy.hpp>
#include <sanguis/server/weapons/attributes/optional_magazine_size.hpp>
#include <sanguis/server/weapons/states/backswing_fwd.hpp>
#include <sanguis/server/weapons/states/castpoint_fwd.hpp>
#include <sanguis/server/weapons/states/idle_fwd.hpp>
#include <sanguis/server/weapons/states/reloading_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/state_machine.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::weapons
{

class weapon
    : public boost::statechart::
          state_machine<sanguis::server::weapons::weapon, sanguis::server::weapons::states::idle>
{
  FCPPT_NONMOVABLE(weapon);

protected:
  explicit weapon(sanguis::server::weapons::parameters const &);

public:
  ~weapon() override = 0;

  void owner(sanguis::server::entities::optional_with_weapon_ref const &);

  void attack();

  void reload();

  void stop();

  void update();

  void tick(sanguis::duration const &);

  [[nodiscard]] sanguis::weapon_type type() const;

  [[nodiscard]] sanguis::server::weapons::attributes::magazine_size magazine_size() const;

  [[nodiscard]] bool in_range(sanguis::server::weapons::target const &) const;

  [[nodiscard]] bool owner_target_in_range() const;

  [[nodiscard]] sanguis::weapon_description description() const;

  [[nodiscard]] virtual sanguis::weapon_attribute_vector attributes() const = 0;

  [[nodiscard]] virtual sanguis::server::weapons::unique_ptr clone() const = 0;

protected:
  [[nodiscard]] virtual sanguis::server::weapons::attack_result
  do_attack(sanguis::server::weapons::attack const &) = 0;

  virtual void owner_lost();

  [[nodiscard]] sanguis::diff_clock const &diff_clock() const;

  [[nodiscard]] sanguis::random_generator &random_generator() const;

  [[nodiscard]] sanguis::server::weapons::log const &log() const;

  [[nodiscard]] sanguis::server::entities::with_weapon &owner() const;

  [[nodiscard]] sanguis::server::weapons::parameters parameters() const;

private:
  friend class sanguis::server::weapons::states::idle;
  friend class sanguis::server::weapons::states::reloading;
  friend class sanguis::server::weapons::states::backswing;
  friend class sanguis::server::weapons::states::castpoint;

  void weapon_status(sanguis::weapon_status);

  void reload_time(sanguis::duration);

  void reset_magazine();

  void use_magazine_item();

  [[nodiscard]] bool magazine_empty() const;

  [[nodiscard]] sanguis::server::weapons::attributes::optional_accuracy accuracy() const;

  [[nodiscard]] sanguis::server::weapons::cast_point cast_point() const;

  [[nodiscard]] sanguis::server::weapons::backswing_time backswing_time() const;

  [[nodiscard]] sanguis::server::weapons::optional_reload_time reload_time() const;

  [[nodiscard]] sanguis::magazine_remaining magazine_remaining() const;

  void update_magazine_remaining();

  sanguis::diff_clock diff_clock_;

  sanguis::random_generator_ref const random_generator_;

  sanguis::server::weapons::log_cref const log_;

  sanguis::weapon_type const type_;

  sanguis::server::weapons::attributes::optional_accuracy const accuracy_;

  sanguis::server::weapons::range const range_;

  using optional_magazine_used = fcppt::optional::object<sanguis::magazine_type>;

  optional_magazine_used magazine_used_;

  sanguis::server::weapons::attributes::optional_magazine_size const magazine_size_;

  sanguis::server::weapons::cast_point const cast_point_;

  sanguis::server::weapons::backswing_time const backswing_time_;

  sanguis::server::weapons::optional_reload_time const reload_time_;

  sanguis::server::entities::optional_with_weapon_ref owner_;
};

}

#endif
