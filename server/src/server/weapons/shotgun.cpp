#include <sanguis/random_generator.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/random_variate.hpp>
#include <sanguis/weapon_attribute_type.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/damage/full.hpp>
#include <sanguis/server/damage/make_array.hpp>
#include <sanguis/server/damage/piercing.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/modify_damages.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/projectiles/simple_bullet.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/attack.hpp>
#include <sanguis/server/weapons/attack_result.hpp>
#include <sanguis/server/weapons/common_parameters_fwd.hpp>
#include <sanguis/server/weapons/optional_reload_time.hpp>
#include <sanguis/server/weapons/parameters.hpp>
#include <sanguis/server/weapons/shells.hpp>
#include <sanguis/server/weapons/shotgun.hpp>
#include <sanguis/server/weapons/shotgun_parameters.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/attributes/damage.hpp>
#include <sanguis/server/weapons/attributes/make.hpp>
#include <sanguis/server/weapons/attributes/make_damage.hpp>
#include <sanguis/server/weapons/attributes/optional_accuracy.hpp>
#include <sanguis/server/weapons/attributes/optional_magazine_size.hpp>
#include <sanguis/server/weapons/attributes/spread_radius.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/repeat.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/normal.hpp>

sanguis::server::weapons::shotgun::shotgun(
    sanguis::server::weapons::common_parameters const &_common_parameters,
    sanguis::weapon_type const _weapon_type,
    sanguis::server::weapons::shotgun_parameters const &_parameters)
    : sanguis::server::weapons::weapon(sanguis::server::weapons::parameters{
          _common_parameters,
          _weapon_type,
          sanguis::server::weapons::attributes::optional_accuracy(_parameters.accuracy()),
          _parameters.range(),
          sanguis::server::weapons::attributes::optional_magazine_size(_parameters.magazine_size()),
          _parameters.backswing_time(),
          _parameters.cast_point(),
          sanguis::server::weapons::optional_reload_time(_parameters.reload_time())}),
      spread_radius_(_parameters.spread_radius()),
      shells_(_parameters.shells()),
      damage_(_parameters.damage())
{
}

sanguis::server::weapons::shotgun::~shotgun() = default;

sanguis::server::weapons::shotgun::shotgun(
    sanguis::server::weapons::parameters const &_parameters,
    sanguis::server::weapons::attributes::spread_radius const _spread_radius,
    sanguis::server::weapons::shells const _shells,
    sanguis::server::weapons::attributes::damage const _damage)
    : sanguis::server::weapons::weapon{_parameters},
      spread_radius_{_spread_radius},
      shells_{_shells},
      damage_{_damage}
{
}

sanguis::server::weapons::unique_ptr sanguis::server::weapons::shotgun::clone() const
{
  return fcppt::unique_ptr_to_base<sanguis::server::weapons::weapon>(
      fcppt::make_unique_ptr<sanguis::server::weapons::shotgun>(
          this->parameters(), spread_radius_, shells_, damage_));
}

sanguis::server::weapons::attack_result
sanguis::server::weapons::shotgun::do_attack(sanguis::server::weapons::attack const &_attack)
{
  using angle_distribution = fcppt::random::distribution::basic<
      fcppt::random::distribution::parameters::normal<sanguis::server::space_unit>>;

  sanguis::random_variate<angle_distribution> angle_rng(
      fcppt::make_ref(this->random_generator()),
      angle_distribution(
          angle_distribution::param_type::mean(_attack.angle().get()),
          angle_distribution::param_type::stddev(spread_radius_.value().get())));

  fcppt::algorithm::repeat(
      shells_.get(),
      [&angle_rng, &_attack, this]()
      {
        sanguis::server::angle const angle(angle_rng());

        sanguis::server::environment::insert_no_result(
            _attack.environment(),
            fcppt::unique_ptr_to_base<sanguis::server::entities::with_id>(
                fcppt::make_unique_ptr<sanguis::server::entities::projectiles::simple_bullet>(
                    _attack.environment().load_context(),
                    this->owner().team(),
                    damage_.value(),
                    sanguis::server::entities::modify_damages(
                        this->owner(),
                        sanguis::server::damage::make_array(
                            {sanguis::server::damage::piercing = sanguis::server::damage::full})),
                    sanguis::server::direction(angle.get()))),
            sanguis::server::entities::insert_parameters(this->owner().center(), angle));
      });

  return sanguis::server::weapons::attack_result::success;
}

sanguis::weapon_attribute_vector sanguis::server::weapons::shotgun::attributes() const
{
  return sanguis::weapon_attribute_vector{
      sanguis::server::weapons::attributes::make_damage(damage_),
      sanguis::server::weapons::attributes::make(
          sanguis::weapon_attribute_type::spread_radius, spread_radius_)};
}
