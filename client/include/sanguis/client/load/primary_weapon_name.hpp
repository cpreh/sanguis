#ifndef SANGUIS_CLIENT_LOAD_PRIMARY_WEAPON_NAME_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_PRIMARY_WEAPON_NAME_HPP_INCLUDED

#include <sanguis/primary_weapon_type_fwd.hpp>
#include <fcppt/string.hpp>


namespace sanguis
{
namespace client
{
namespace load
{

fcppt::string
primary_weapon_name(
	sanguis::primary_weapon_type
);

}
}
}

#endif