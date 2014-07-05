#ifndef SANGUIS_SERVER_WEAPONS_ROCKET_LAUNCHER_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_ROCKET_LAUNCHER_PARAMETERS_HPP_INCLUDED

#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/aoe.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/rocket_launcher_parameters_fwd.hpp>
#include <sanguis/server/weapons/attributes/aoe.hpp>
#include <sanguis/server/weapons/attributes/damage.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

class rocket_launcher_parameters
{
	FCPPT_NONASSIGNABLE(
		rocket_launcher_parameters
	);
public:
	rocket_launcher_parameters(
		sanguis::server::weapons::damage,
		sanguis::server::weapons::aoe,
		sanguis::server::weapons::accuracy,
		sanguis::server::weapons::backswing_time,
		sanguis::server::weapons::cast_point,
		sanguis::server::weapons::magazine_size,
		sanguis::server::weapons::reload_time,
		sanguis::server::weapons::range
	);

	sanguis::server::weapons::attributes::damage const
	damage() const;

	sanguis::server::weapons::attributes::aoe const
	aoe() const;

	sanguis::server::weapons::accuracy const
	accuracy() const;

	sanguis::server::weapons::backswing_time const
	backswing_time() const;

	sanguis::server::weapons::cast_point const
	cast_point() const;

	sanguis::server::weapons::magazine_size const
	magazine_size() const;

	sanguis::server::weapons::reload_time const
	reload_time() const;

	sanguis::server::weapons::range const
	range() const;

	void
	extra_damage(
		sanguis::server::weapons::damage
	);

	void
	extra_aoe(
		sanguis::server::weapons::aoe
	);
private:
	sanguis::server::weapons::attributes::damage damage_;

	sanguis::server::weapons::attributes::aoe aoe_;

	sanguis::server::weapons::accuracy const accuracy_;

	sanguis::server::weapons::backswing_time const backswing_time_;

	sanguis::server::weapons::cast_point const cast_point_;

	sanguis::server::weapons::magazine_size const magazine_size_;

	sanguis::server::weapons::reload_time const reload_time_;

	sanguis::server::weapons::range const range_;
};

}
}
}

#endif
