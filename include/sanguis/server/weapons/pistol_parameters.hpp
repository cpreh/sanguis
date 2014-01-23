#ifndef SANGUIS_SERVER_WEAPONS_PISTOL_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_PISTOL_PARAMETERS_HPP_INCLUDED

#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/pistol_parameters_fwd.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/attributes/accuracy.hpp>
#include <sanguis/server/weapons/attributes/damage.hpp>
#include <sanguis/server/weapons/attributes/magazine_size.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

class pistol_parameters
{
	FCPPT_NONASSIGNABLE(
		pistol_parameters
	);
public:
	pistol_parameters(
		sanguis::server::weapons::accuracy,
		sanguis::server::weapons::base_cooldown,
		sanguis::server::weapons::damage,
		sanguis::server::weapons::cast_point,
		sanguis::server::weapons::magazine_size,
		sanguis::server::weapons::reload_time,
		sanguis::server::weapons::range
	);

	sanguis::server::weapons::attributes::accuracy const
	accuracy() const;

	sanguis::server::weapons::base_cooldown const
	base_cooldown() const;

	sanguis::server::weapons::attributes::damage const
	damage() const;

	sanguis::server::weapons::cast_point const
	cast_point() const;

	sanguis::server::weapons::attributes::magazine_size const
	magazine_size() const;

	sanguis::server::weapons::reload_time const
	reload_time() const;

	sanguis::server::weapons::range const
	range() const;

	void
	extra_accuracy(
		sanguis::server::weapons::accuracy
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

	sanguis::server::weapons::base_cooldown const base_cooldown_;

	sanguis::server::weapons::attributes::damage damage_;

	sanguis::server::weapons::cast_point const cast_point_;

	sanguis::server::weapons::attributes::magazine_size magazine_size_;

	sanguis::server::weapons::reload_time const reload_time_;

	sanguis::server::weapons::range const range_;
};

}
}
}

#endif
