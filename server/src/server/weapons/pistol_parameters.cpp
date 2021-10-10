#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/pistol_parameters.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/attributes/accuracy.hpp>
#include <sanguis/server/weapons/attributes/damage.hpp>
#include <sanguis/server/weapons/attributes/magazine_size.hpp>

sanguis::server::weapons::pistol_parameters::pistol_parameters(
    sanguis::server::weapons::accuracy const _accuracy,
    sanguis::server::weapons::backswing_time const _backswing_time,
    sanguis::server::weapons::damage const _damage,
    sanguis::server::weapons::cast_point const _cast_point,
    sanguis::server::weapons::magazine_size const _magazine_size,
    sanguis::server::weapons::reload_time const _reload_time,
    sanguis::server::weapons::range const _range)
    : accuracy_(_accuracy),
      backswing_time_(_backswing_time),
      damage_(_damage),
      cast_point_(_cast_point),
      magazine_size_(_magazine_size),
      reload_time_(_reload_time),
      range_(_range)
{
}

sanguis::server::weapons::attributes::accuracy
sanguis::server::weapons::pistol_parameters::accuracy() const
{
  return accuracy_;
}

sanguis::server::weapons::backswing_time
sanguis::server::weapons::pistol_parameters::backswing_time() const
{
  return backswing_time_;
}

sanguis::server::weapons::attributes::damage
sanguis::server::weapons::pistol_parameters::damage() const
{
  return damage_;
}

sanguis::server::weapons::cast_point sanguis::server::weapons::pistol_parameters::cast_point() const
{
  return cast_point_;
}

sanguis::server::weapons::attributes::magazine_size
sanguis::server::weapons::pistol_parameters::magazine_size() const
{
  return magazine_size_;
}

sanguis::server::weapons::reload_time
sanguis::server::weapons::pistol_parameters::reload_time() const
{
  return reload_time_;
}

sanguis::server::weapons::range sanguis::server::weapons::pistol_parameters::range() const
{
  return range_;
}

void sanguis::server::weapons::pistol_parameters::extra_accuracy(
    sanguis::server::weapons::accuracy const _accuracy)
{
  accuracy_.extra(_accuracy);
}

void sanguis::server::weapons::pistol_parameters::extra_damage(
    sanguis::server::weapons::damage const _damage)
{
  damage_.extra(_damage);
}

void sanguis::server::weapons::pistol_parameters::extra_magazine_size(
    sanguis::server::weapons::magazine_size const _magazine_size)
{
  magazine_size_.extra(_magazine_size);
}
