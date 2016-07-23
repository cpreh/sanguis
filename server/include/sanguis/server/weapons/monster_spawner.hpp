#ifndef SANGUIS_SERVER_WEAPONS_MONSTER_SPAWNER_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MONSTER_SPAWNER_HPP_INCLUDED

#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/server/weapons/attack_fwd.hpp>
#include <sanguis/server/weapons/attack_result_fwd.hpp>
#include <sanguis/server/weapons/common_parameters.hpp>
#include <sanguis/server/weapons/parameters_fwd.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
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
	explicit
	monster_spawner(
		sanguis::server::weapons::common_parameters const &
	);

	~monster_spawner()
	override;

	explicit
	monster_spawner(
		sanguis::server::weapons::parameters const &
	);
private:
	sanguis::server::weapons::unique_ptr
	clone() const
	override;

	sanguis::server::weapons::attack_result
	do_attack(
		sanguis::server::weapons::attack const &
	)
	override;

	sanguis::weapon_attribute_vector
	attributes() const
	override;

	sanguis::server::weapons::common_parameters const common_parameters_;
};

}
}
}

#endif
