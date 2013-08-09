#ifndef SANGUIS_LOAD_WEAPON_PICKUP_NAME_HPP_INCLUDED
#define SANGUIS_LOAD_WEAPON_PICKUP_NAME_HPP_INCLUDED

#include <sanguis/weapon_type_fwd.hpp>
#include <fcppt/string.hpp>


namespace sanguis
{
namespace load
{

fcppt::string
weapon_pickup_name(
	sanguis::weapon_type const &
);

}
}

#endif
