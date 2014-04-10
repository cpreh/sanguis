#ifndef SANGUIS_SERVER_WEAPONS_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_CREATE_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type_fwd.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

sanguis::server::weapons::unique_ptr
create(
	sanguis::diff_clock const &,
	sanguis::random_generator &,
	sanguis::weapon_type,
	sanguis::server::entities::enemies::difficulty
);

}
}
}

#endif
