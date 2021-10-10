#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/aoe.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/rocket_launcher_parameters.hpp>
#include <sanguis/server/weapons/attributes/aoe.hpp>
#include <sanguis/server/weapons/attributes/damage.hpp>

sanguis::server::weapons::rocket_launcher_parameters::rocket_launcher_parameters(
    sanguis::server::weapons::damage const _damage,
    sanguis::server::weapons::aoe const _aoe,
    sanguis::server::weapons::accuracy const _accuracy,
    sanguis::server::weapons::backswing_time const _backswing_time,
    sanguis::server::weapons::cast_point const _cast_point,
    sanguis::server::weapons::magazine_size const _magazine_size,
    sanguis::server::weapons::reload_time const _reload_time,
    sanguis::server::weapons::range const _range)
    : damage_(_damage),
      aoe_(_aoe),
      accuracy_(_accuracy),
      backswing_time_(_backswing_time),
      cast_point_(_cast_point),
      magazine_size_(_magazine_size),
      reload_time_(_reload_time),
      range_(_range)
{
}

sanguis::server::weapons::attributes::damage
sanguis::server::weapons::rocket_launcher_parameters::damage() const
{
  return damage_;
}

sanguis::server::weapons::attributes::aoe
sanguis::server::weapons::rocket_launcher_parameters::aoe() const
{
  return aoe_;
}

sanguis::server::weapons::accuracy
sanguis::server::weapons::rocket_launcher_parameters::accuracy() const
{
  return accuracy_;
}

sanguis::server::weapons::backswing_time
sanguis::server::weapons::rocket_launcher_parameters::backswing_time() const
{
  return backswing_time_;
}

sanguis::server::weapons::cast_point
sanguis::server::weapons::rocket_launcher_parameters::cast_point() const
{
  return cast_point_;
}

sanguis::server::weapons::magazine_size
sanguis::server::weapons::rocket_launcher_parameters::magazine_size() const
{
  return magazine_size_;
}

sanguis::server::weapons::reload_time
sanguis::server::weapons::rocket_launcher_parameters::reload_time() const
{
  return reload_time_;
}

sanguis::server::weapons::range sanguis::server::weapons::rocket_launcher_parameters::range() const
{
  return range_;
}

void sanguis::server::weapons::rocket_launcher_parameters::extra_damage(
    sanguis::server::weapons::damage const _damage)
{
  damage_.extra(_damage);
}

void sanguis::server::weapons::rocket_launcher_parameters::extra_aoe(
    sanguis::server::weapons::aoe const _aoe)
{
  aoe_.extra(_aoe);
}
