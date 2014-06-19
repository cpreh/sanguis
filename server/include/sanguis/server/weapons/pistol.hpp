#ifndef SANGUIS_SERVER_WEAPONS_PISTOL_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_PISTOL_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/weapon_type_fwd.hpp>
#include <sanguis/server/weapons/attack_fwd.hpp>
#include <sanguis/server/weapons/attack_result_fwd.hpp>
#include <sanguis/server/weapons/pistol_parameters_fwd.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/attributes/damage.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

class pistol
:
	public sanguis::server::weapons::weapon
{
	FCPPT_NONCOPYABLE(
		pistol
	);
public:
	pistol(
		sanguis::random_generator &,
		sanguis::weapon_type,
		sanguis::server::weapons::pistol_parameters const &
	);

	~pistol()
	override;
private:
	sanguis::server::weapons::attack_result
	do_attack(
		sanguis::server::weapons::attack const &
	)
	override;

	sanguis::weapon_attribute_vector
	attributes() const
	override;

	sanguis::server::weapons::attributes::damage const damage_;
};

}
}
}

#endif
