#ifndef SANGUIS_SERVER_WEAPONS_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_CREATE_HPP_INCLUDED

#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{

unique_ptr
create(
	sanguis::diff_clock const &,
	sanguis::random_generator &,
	weapon_type::type
);

}
}
}

#endif
