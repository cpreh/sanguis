#include <sanguis/server/health.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/sentry_parameters.hpp>
#include <sanguis/server/weapons/attributes/health.hpp>


sanguis::server::weapons::sentry_parameters::sentry_parameters(
	sanguis::server::health const _health,
	sanguis::server::weapons::backswing_time const _backswing_time,
	sanguis::server::weapons::cast_point const _cast_point,
	sanguis::server::weapons::range const _range,
	sanguis::server::weapons::magazine_size const _magazine_size
)
:
	health_(
		_health
	),
	backswing_time_(
		_backswing_time
	),
	cast_point_(
		_cast_point
	),
	range_(
		_range
	),
	magazine_size_(
		_magazine_size
	)
{
}

sanguis::server::weapons::attributes::health const
sanguis::server::weapons::sentry_parameters::health() const
{
	return
		health_;
}

sanguis::server::weapons::backswing_time const
sanguis::server::weapons::sentry_parameters::backswing_time() const
{
	return
		backswing_time_;
}

sanguis::server::weapons::cast_point const
sanguis::server::weapons::sentry_parameters::cast_point() const
{
	return
		cast_point_;
}

sanguis::server::weapons::range const
sanguis::server::weapons::sentry_parameters::range() const
{
	return
		range_;
}

sanguis::server::weapons::magazine_size const
sanguis::server::weapons::sentry_parameters::magazine_size() const
{
	return
		magazine_size_;
}

void
sanguis::server::weapons::sentry_parameters::extra_health(
	sanguis::server::health const _health
)
{
	health_.extra(
		_health
	);
}
