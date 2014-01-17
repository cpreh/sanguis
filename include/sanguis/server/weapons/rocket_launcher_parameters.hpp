#ifndef SANGUIS_SERVER_WEAPONS_ROCKET_LAUNCHER_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_ROCKET_LAUNCHER_PARAMETERS_HPP_INCLUDED

#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/aoe.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/rocket_launcher_parameters_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

class rocket_launcher_parameters
{
public:
	rocket_launcher_parameters(
		sanguis::server::weapons::damage,
		sanguis::server::weapons::aoe,
		sanguis::server::weapons::accuracy,
		sanguis::server::weapons::base_cooldown,
		sanguis::server::weapons::cast_point,
		sanguis::server::weapons::magazine_size,
		sanguis::server::weapons::reload_time,
		sanguis::server::weapons::range
	);

	sanguis::server::weapons::damage const
	damage() const;

	sanguis::server::weapons::aoe const
	aoe() const;

	sanguis::server::weapons::accuracy const
	accuracy() const;

	sanguis::server::weapons::base_cooldown const
	base_cooldown() const;

	sanguis::server::weapons::cast_point const
	cast_point() const;

	sanguis::server::weapons::magazine_size const
	magazine_size() const;

	sanguis::server::weapons::reload_time const
	reload_time() const;

	sanguis::server::weapons::range const
	range() const;

	void
	damage(
		sanguis::server::weapons::damage
	);

	void
	aoe(
		sanguis::server::weapons::aoe
	);
private:
	sanguis::server::weapons::damage damage_;

	sanguis::server::weapons::aoe aoe_;

	sanguis::server::weapons::accuracy accuracy_;

	sanguis::server::weapons::base_cooldown base_cooldown_;

	sanguis::server::weapons::cast_point cast_point_;

	sanguis::server::weapons::magazine_size magazine_size_;

	sanguis::server::weapons::reload_time reload_time_;

	sanguis::server::weapons::range range_;
};

}
}
}

#endif
