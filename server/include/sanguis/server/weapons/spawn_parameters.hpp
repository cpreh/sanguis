#ifndef SANGUIS_SERVER_WEAPONS_SPAWN_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_SPAWN_PARAMETERS_HPP_INCLUDED

#include <sanguis/server/weapons/parameters.hpp>
#include <sanguis/server/weapons/spawn_parameters_fwd.hpp>
#include <sanguis/server/weapons/spawn_weapon.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

class spawn_parameters
{
	FCPPT_NONASSIGNABLE(
		spawn_parameters
	);
public:
	spawn_parameters(
		sanguis::server::weapons::parameters const &,
		sanguis::server::weapons::spawn_weapon const &
	);

	sanguis::server::weapons::parameters const &
	parameters() const;

	sanguis::server::weapons::spawn_weapon const &
	spawn_weapon() const;
private:
	sanguis::server::weapons::parameters const parameters_;

	sanguis::server::weapons::spawn_weapon const spawn_weapon_;
};

}
}
}

#endif
