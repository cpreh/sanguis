#ifndef SANGUIS_WEAPON_STATUS_HPP_INCLUDED
#define SANGUIS_WEAPON_STATUS_HPP_INCLUDED

#include <sanguis/weapon_status_fwd.hpp>


namespace sanguis
{

enum class weapon_status
{
	nothing,
	attacking,
	reloading,
	fcppt_maximum = reloading
};

}

#endif
