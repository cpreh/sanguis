#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/shells.hpp>
#include <sanguis/server/weapons/shotgun_parameters.hpp>
#include <sanguis/server/weapons/spread_radius.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/attributes/accuracy.hpp>
#include <sanguis/server/weapons/attributes/damage.hpp>
#include <sanguis/server/weapons/attributes/magazine_size.hpp>


sanguis::server::weapons::shotgun_parameters::shotgun_parameters(
	sanguis::server::weapons::accuracy const _accuracy,
	sanguis::server::weapons::base_cooldown const _base_cooldown,
	sanguis::server::weapons::cast_point const _cast_point,
	sanguis::server::weapons::spread_radius const _spread_radius,
	sanguis::server::weapons::shells const _shells,
	sanguis::server::weapons::damage const _damage,
	sanguis::server::weapons::magazine_size const _magazine_size,
	sanguis::server::weapons::reload_time const _reload_time,
	sanguis::server::weapons::range const _range
)
:
	accuracy_(
		_accuracy
	),
	base_cooldown_(
		_base_cooldown
	),
	cast_point_(
		_cast_point
	),
	spread_radius_(
		_spread_radius
	),
	shells_(
		_shells
	),
	damage_(
		_damage
	),
	magazine_size_(
		_magazine_size
	),
	reload_time_(
		_reload_time
	),
	range_(
		_range
	)
{
}

sanguis::server::weapons::attributes::accuracy const
sanguis::server::weapons::shotgun_parameters::accuracy() const
{
	return
		accuracy_;
}

sanguis::server::weapons::base_cooldown const
sanguis::server::weapons::shotgun_parameters::base_cooldown() const
{
	return
		base_cooldown_;
}

sanguis::server::weapons::cast_point const
sanguis::server::weapons::shotgun_parameters::cast_point() const
{
	return
		cast_point_;
}

sanguis::server::weapons::spread_radius const
sanguis::server::weapons::shotgun_parameters::spread_radius() const
{
	return
		spread_radius_;
}

sanguis::server::weapons::shells const
sanguis::server::weapons::shotgun_parameters::shells() const
{
	return
		shells_;
}

sanguis::server::weapons::attributes::damage const
sanguis::server::weapons::shotgun_parameters::damage() const
{
	return
		damage_;
}

sanguis::server::weapons::attributes::magazine_size const
sanguis::server::weapons::shotgun_parameters::magazine_size() const
{
	return
		magazine_size_;
}

sanguis::server::weapons::reload_time const
sanguis::server::weapons::shotgun_parameters::reload_time() const
{
	return
		reload_time_;
}

sanguis::server::weapons::range const
sanguis::server::weapons::shotgun_parameters::range() const
{
	return
		range_;
}

void
sanguis::server::weapons::shotgun_parameters::extra_accuracy(
	sanguis::server::weapons::accuracy const _accuracy
)
{
	accuracy_.extra(
		_accuracy
	);
}

void
sanguis::server::weapons::shotgun_parameters::spread_radius(
	sanguis::server::weapons::spread_radius const _spread_radius
)
{
	spread_radius_ =
		_spread_radius;
}

void
sanguis::server::weapons::shotgun_parameters::extra_damage(
	sanguis::server::weapons::damage const _damage
)
{
	damage_.extra(
		_damage
	);
}

void
sanguis::server::weapons::shotgun_parameters::extra_magazine_size(
	sanguis::server::weapons::magazine_size const _magazine_size
)
{
	magazine_size_.extra(
		_magazine_size
	);
}
