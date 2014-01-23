#ifndef SANGUIS_SERVER_WEAPONS_SHOTGUN_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_SHOTGUN_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/weapon_type_fwd.hpp>
#include <sanguis/server/weapons/attack_result_fwd.hpp>
#include <sanguis/server/weapons/delayed_attack_fwd.hpp>
#include <sanguis/server/weapons/shells.hpp>
#include <sanguis/server/weapons/shotgun_parameters_fwd.hpp>
#include <sanguis/server/weapons/spread_radius.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/attributes/damage.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

class shotgun
:
	public sanguis::server::weapons::weapon
{
	FCPPT_NONCOPYABLE(
		shotgun
	);
public:
	shotgun(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		sanguis::weapon_type,
		sanguis::server::weapons::shotgun_parameters const &
	);

	~shotgun();
private:
	sanguis::server::weapons::attack_result
	do_attack(
		sanguis::server::weapons::delayed_attack const &
	)
	override;

	sanguis::weapon_attribute_vector
	attributes() const
	override;

	sanguis::random_generator &random_generator_;

	sanguis::server::weapons::spread_radius const spread_radius_;

	sanguis::server::weapons::shells const shells_;

	sanguis::server::weapons::attributes::damage const damage_;
};

}
}
}

#endif
