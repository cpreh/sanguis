#ifndef SANGUIS_SERVER_WEAPONS_GRENADE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_GRENADE_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/server/weapons/attack_result_fwd.hpp>
#include <sanguis/server/weapons/delayed_attack_fwd.hpp>
#include <sanguis/server/weapons/grenade_parameters_fwd.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/attributes/aoe.hpp>
#include <sanguis/server/weapons/attributes/damage.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

class grenade
:
	public sanguis::server::weapons::weapon
{
	FCPPT_NONCOPYABLE(
		grenade
	);
public:
	grenade(
		sanguis::random_generator &,
		sanguis::server::weapons::grenade_parameters const &
	);

	~grenade();
private:
	sanguis::server::weapons::attack_result
	do_attack(
		sanguis::server::weapons::delayed_attack const &
	)
	override;

	sanguis::weapon_attribute_vector
	attributes() const
	override;

	sanguis::server::weapons::attributes::damage const damage_;

	sanguis::server::weapons::attributes::aoe const aoe_;
};

}
}
}

#endif
