#ifndef SANGUIS_SERVER_WEAPONS_PISTOL_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_PISTOL_HPP_INCLUDED

#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/weapon_type_fwd.hpp>
#include <sanguis/server/weapons/attack_fwd.hpp>
#include <sanguis/server/weapons/attack_result_fwd.hpp>
#include <sanguis/server/weapons/common_parameters_fwd.hpp>
#include <sanguis/server/weapons/parameters_fwd.hpp>
#include <sanguis/server/weapons/pistol_parameters_fwd.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/attributes/damage.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::server::weapons
{

class pistol
:
	public sanguis::server::weapons::weapon
{
	FCPPT_NONMOVABLE(
		pistol
	);
public:
	pistol(
		sanguis::server::weapons::common_parameters const &,
		sanguis::weapon_type,
		sanguis::server::weapons::pistol_parameters const &
	);

	~pistol()
	override;

	pistol(
		sanguis::server::weapons::parameters const &,
		sanguis::server::weapons::attributes::damage
	);
private:
	[[nodiscard]]
	sanguis::server::weapons::unique_ptr
	clone() const
	override;

	[[nodiscard]]
	sanguis::server::weapons::attack_result
	do_attack(
		sanguis::server::weapons::attack const &
	)
	override;

	[[nodiscard]]
	sanguis::weapon_attribute_vector
	attributes() const
	override;

	sanguis::server::weapons::attributes::damage const damage_;
};

}

#endif
