#ifndef SANGUIS_SERVER_WEAPONS_BASE_COOLDOWN_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_BASE_COOLDOWN_HPP_INCLUDED

#include "../../time_delta.hpp"
#include <fcppt/strong_typedef.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::time_delta,
	base_cooldown
);

}
}
}

#endif
