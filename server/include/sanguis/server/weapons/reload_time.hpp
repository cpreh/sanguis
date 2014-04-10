#ifndef SANGUIS_SERVER_WEAPONS_RELOAD_TIME_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_RELOAD_TIME_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::duration,
	reload_time
);

}
}
}

#endif
