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
	sentry_pickup,
	fcppt_maximum = sentry_pickup
};

}

#endif
