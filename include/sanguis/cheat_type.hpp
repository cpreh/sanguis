#ifndef SANGUIS_CHEAT_TYPE_HPP_INCLUDED
#define SANGUIS_CHEAT_TYPE_HPP_INCLUDED

#include <sanguis/cheat_type_fwd.hpp>


namespace sanguis
{

enum class cheat_type
{
	exp,
	kill,
	monster_pickup,
	fcppt_maximum = monster_pickup
};

}

#endif
