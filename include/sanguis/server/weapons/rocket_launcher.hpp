#ifndef SANGUIS_SERVER_WEAPONS_ROCKET_LAUNCHER_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_ROCKET_LAUNCHER_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/string_vector.hpp>
#include <sanguis/weapon_type_fwd.hpp>
#include <sanguis/server/weapons/aoe.hpp>
#include <sanguis/server/weapons/attack_result_fwd.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/delayed_attack_fwd.hpp>
#include <sanguis/server/weapons/rocket_launcher_parameters_fwd.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

class rocket_launcher
:
	public sanguis::server::weapons::weapon
{
	FCPPT_NONCOPYABLE(
		rocket_launcher
	);
public:
	rocket_launcher(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		sanguis::weapon_type,
		sanguis::server::weapons::rocket_launcher_parameters const &
	);

	~rocket_launcher();
private:
	sanguis::server::weapons::attack_result
	do_attack(
		sanguis::server::weapons::delayed_attack const &
	)
	override;

	sanguis::string_vector
	attributes() const
	override;

	sanguis::server::weapons::damage const damage_;

	sanguis::server::weapons::aoe const aoe_;
};

}
}
}

#endif
