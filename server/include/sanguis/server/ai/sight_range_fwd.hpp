#ifndef SANGUIS_SERVER_AI_SIGHT_RANGE_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_AI_SIGHT_RANGE_FWD_HPP_INCLUDED

#include <sanguis/server/space_unit.hpp>
#include <fcppt/make_strong_typedef.hpp>


namespace sanguis::server::ai
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::server::space_unit,
	sight_range
);

}

#endif
