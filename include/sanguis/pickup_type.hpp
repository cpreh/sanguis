#ifndef SANGUIS_PICKUP_TYPE_HPP_INCLUDED
#define SANGUIS_PICKUP_TYPE_HPP_INCLUDED

#include <sanguis/pickup_type_fwd.hpp>


namespace sanguis
{

enum class pickup_type
{
	health,
	monster,
	weapon,
	fcppt_maximum = weapon
};

}

#endif
