#ifndef SANGUIS_SERVER_WEAPONS_GRENADE_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_GRENADE_PARAMETERS_HPP_INCLUDED

#include <sanguis/server/weapons/aoe.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/grenade_parameters_fwd.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/attributes/aoe.hpp>
#include <sanguis/server/weapons/attributes/damage.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

class grenade_parameters
{
public:
	grenade_parameters(
		sanguis::server::weapons::backswing_time,
		sanguis::server::weapons::damage,
		sanguis::server::weapons::aoe,
		sanguis::server::weapons::cast_point,
		sanguis::server::weapons::range
	);

	[[nodiscard]]
	sanguis::server::weapons::backswing_time
	backswing_time() const;

	[[nodiscard]]
	sanguis::server::weapons::attributes::damage
	damage() const;

	[[nodiscard]]
	sanguis::server::weapons::attributes::aoe
	aoe() const;

	[[nodiscard]]
	sanguis::server::weapons::cast_point
	cast_point() const;

	[[nodiscard]]
	sanguis::server::weapons::range
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
	sanguis::server::weapons::backswing_time backswing_time_;

	sanguis::server::weapons::attributes::damage damage_;

	sanguis::server::weapons::attributes::aoe aoe_;

	sanguis::server::weapons::cast_point cast_point_;

	sanguis::server::weapons::range range_;
};

}
}
}

#endif
