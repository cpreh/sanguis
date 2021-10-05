#ifndef SANGUIS_SERVER_WEAPONS_BACKSWING_TIME_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_BACKSWING_TIME_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis::server::weapons
{

FCPPT_DECLARE_STRONG_TYPEDEF(
	sanguis::duration,
	backswing_time
);

}

#endif
