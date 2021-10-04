#ifndef SANGUIS_SERVER_WEAPONS_MELEE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MELEE_HPP_INCLUDED

#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/weapons/attack_fwd.hpp>
#include <sanguis/server/weapons/attack_result_fwd.hpp>
#include <sanguis/server/weapons/common_parameters_fwd.hpp>
#include <sanguis/server/weapons/melee_parameters_fwd.hpp>
#include <sanguis/server/weapons/parameters_fwd.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/attributes/damage.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::server::weapons
{

class melee
:
	public sanguis::server::weapons::weapon
{
	FCPPT_NONMOVABLE(
		melee
	);
public:
	melee(
		sanguis::server::weapons::common_parameters const &,
		sanguis::server::weapons::melee_parameters const &
	);

	~melee()
	override;

	melee(
		sanguis::server::weapons::parameters const &,
		sanguis::server::weapons::attributes::damage,
		sanguis::server::damage::array const &
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

	sanguis::server::damage::array const damage_values_;
};

}

#endif
