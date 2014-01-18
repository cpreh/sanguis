#ifndef SANGUIS_SERVER_WEAPONS_GRENADE_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_GRENADE_PARAMETERS_HPP_INCLUDED

#include <sanguis/server/weapons/aoe.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/grenade_parameters_fwd.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/range.hpp>



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
		sanguis::server::weapons::base_cooldown,
		sanguis::server::weapons::damage,
		sanguis::server::weapons::aoe,
		sanguis::server::weapons::cast_point,
		sanguis::server::weapons::range,
		sanguis::server::weapons::magazine_size
	);

	sanguis::server::weapons::base_cooldown const
	base_cooldown() const;

	sanguis::server::weapons::damage const
	damage() const;

	sanguis::server::weapons::aoe const
	aoe() const;

	sanguis::server::weapons::cast_point const
	cast_point() const;

	sanguis::server::weapons::range const
	range() const;

	sanguis::server::weapons::magazine_size const
	magazine_size() const;

	void
	damage(
		sanguis::server::weapons::damage
	);

	void
	aoe(
		sanguis::server::weapons::aoe
	);

	void
	magazine_size(
		sanguis::server::weapons::magazine_size
	);
private:
	sanguis::server::weapons::base_cooldown base_cooldown_;

	sanguis::server::weapons::damage damage_;

	sanguis::server::weapons::aoe aoe_;

	sanguis::server::weapons::cast_point cast_point_;

	sanguis::server::weapons::range range_;

	sanguis::server::weapons::magazine_size magazine_size_;
};

}
}
}

#endif
