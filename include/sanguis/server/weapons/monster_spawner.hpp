#ifndef SANGUIS_SERVER_WEAPONS_MONSTER_SPAWNER_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MONSTER_SPAWNER_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/server/weapons/attack_result_fwd.hpp>
#include <sanguis/server/weapons/delayed_attack_fwd.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

class monster_spawner
:
	public sanguis::server::weapons::weapon
{
	FCPPT_NONCOPYABLE(
		monster_spawner
	);
public:
	monster_spawner(
		sanguis::diff_clock const &,
		sanguis::random_generator &
	);

	~monster_spawner();
private:
	sanguis::server::weapons::attack_result
	do_attack(
		sanguis::server::weapons::delayed_attack const &
	)
	override;

	sanguis::weapon_attribute_vector
	attributes() const
	override;
};

}
}
}

#endif
