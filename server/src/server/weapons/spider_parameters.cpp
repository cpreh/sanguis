#include <sanguis/server/health.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/spider_parameters.hpp>
#include <sanguis/server/weapons/attributes/health.hpp>

sanguis::server::weapons::spider_parameters::spider_parameters(
    sanguis::server::health const _health,
    sanguis::server::weapons::backswing_time const _backswing_time,
    sanguis::server::weapons::cast_point const _cast_point,
    sanguis::server::weapons::range const _range)
    : health_(_health), backswing_time_(_backswing_time), cast_point_(_cast_point), range_(_range)
{
}

sanguis::server::weapons::attributes::health
sanguis::server::weapons::spider_parameters::health() const
{
  return health_;
}

sanguis::server::weapons::backswing_time
sanguis::server::weapons::spider_parameters::backswing_time() const
{
  return backswing_time_;
}

sanguis::server::weapons::cast_point sanguis::server::weapons::spider_parameters::cast_point() const
{
  return cast_point_;
}

sanguis::server::weapons::range sanguis::server::weapons::spider_parameters::range() const
{
  return range_;
}

void sanguis::server::weapons::spider_parameters::extra_health(
    sanguis::server::health const _health)
{
  health_.extra(_health);
}
