#ifndef SANGUIS_SERVER_WEAPONS_SHOTGUN_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_SHOTGUN_PARAMETERS_HPP_INCLUDED

#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/shells.hpp>
#include <sanguis/server/weapons/shotgun_parameters_fwd.hpp>
#include <sanguis/server/weapons/spread_radius.hpp>
#include <sanguis/server/weapons/attributes/accuracy.hpp>
#include <sanguis/server/weapons/attributes/damage.hpp>
#include <sanguis/server/weapons/attributes/magazine_size.hpp>
#include <sanguis/server/weapons/attributes/spread_radius.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

class shotgun_parameters
{
public:
	shotgun_parameters(
		sanguis::server::weapons::accuracy,
		sanguis::server::weapons::backswing_time,
		sanguis::server::weapons::cast_point,
		sanguis::server::weapons::spread_radius,
		sanguis::server::weapons::shells,
		sanguis::server::weapons::damage,
		sanguis::server::weapons::magazine_size,
		sanguis::server::weapons::reload_time,
		sanguis::server::weapons::range
	);

	sanguis::server::weapons::attributes::accuracy
	accuracy() const;

	sanguis::server::weapons::backswing_time
	backswing_time() const;

	sanguis::server::weapons::cast_point
	cast_point() const;

	sanguis::server::weapons::attributes::spread_radius
	spread_radius() const;

	sanguis::server::weapons::shells
	shells() const;

	sanguis::server::weapons::attributes::damage
	damage() const;

	sanguis::server::weapons::attributes::magazine_size
	magazine_size() const;

	sanguis::server::weapons::reload_time
	reload_time() const;

	sanguis::server::weapons::range
	range() const;

	void
	extra_accuracy(
		sanguis::server::weapons::accuracy
	);

	void
	extra_spread_radius(
		sanguis::server::weapons::spread_radius
	);

	void
	extra_damage(
		sanguis::server::weapons::damage
	);

	void
	extra_magazine_size(
		sanguis::server::weapons::magazine_size
	);
private:
	sanguis::server::weapons::attributes::accuracy accuracy_;

	sanguis::server::weapons::backswing_time backswing_time_;

	sanguis::server::weapons::cast_point cast_point_;

	sanguis::server::weapons::attributes::spread_radius spread_radius_;

	sanguis::server::weapons::shells shells_;

	sanguis::server::weapons::attributes::damage damage_;

	sanguis::server::weapons::attributes::magazine_size magazine_size_;

	sanguis::server::weapons::reload_time reload_time_;

	sanguis::server::weapons::range range_;
};

}
}
}

#endif
