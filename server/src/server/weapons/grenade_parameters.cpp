#include <sanguis/server/weapons/aoe.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/grenade_parameters.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/attributes/aoe.hpp>
#include <sanguis/server/weapons/attributes/damage.hpp>
#include <sanguis/server/weapons/attributes/magazine_size.hpp>


sanguis::server::weapons::grenade_parameters::grenade_parameters(
	sanguis::server::weapons::backswing_time const _backswing_time,
	sanguis::server::weapons::damage const _damage,
	sanguis::server::weapons::aoe const _aoe,
	sanguis::server::weapons::cast_point const _cast_point,
	sanguis::server::weapons::range const _range,
	sanguis::server::weapons::magazine_size const _magazine_size
)
:
	backswing_time_(
		_backswing_time
	),
	damage_(
		_damage
	),
	aoe_(
		_aoe
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

sanguis::server::weapons::backswing_time const
sanguis::server::weapons::grenade_parameters::backswing_time() const
{
	return
		backswing_time_;
}

sanguis::server::weapons::attributes::damage const
sanguis::server::weapons::grenade_parameters::damage() const
{
	return
		damage_;
}

sanguis::server::weapons::attributes::aoe const
sanguis::server::weapons::grenade_parameters::aoe() const
{
	return
		aoe_;
}

sanguis::server::weapons::cast_point const
sanguis::server::weapons::grenade_parameters::cast_point() const
{
	return
		cast_point_;
}

sanguis::server::weapons::range const
sanguis::server::weapons::grenade_parameters::range() const
{
	return
		range_;
}

sanguis::server::weapons::attributes::magazine_size const
sanguis::server::weapons::grenade_parameters::magazine_size() const
{
	return
		magazine_size_;
}

void
sanguis::server::weapons::grenade_parameters::extra_damage(
	sanguis::server::weapons::damage const _damage
)
{
	damage_.extra(
		_damage
	);
}

void
sanguis::server::weapons::grenade_parameters::extra_aoe(
	sanguis::server::weapons::aoe const _aoe
)
{
	aoe_.extra(
		_aoe
	);
}

void
sanguis::server::weapons::grenade_parameters::extra_magazine_size(
	sanguis::server::weapons::magazine_size const _magazine_size
)
{
	magazine_size_.extra(
		_magazine_size
	);
}
