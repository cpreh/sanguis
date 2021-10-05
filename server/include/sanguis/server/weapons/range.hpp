#ifndef SANGUIS_SERVER_WEAPONS_RANGE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_RANGE_HPP_INCLUDED

#include <sanguis/server/space_unit.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis::server::weapons
{

FCPPT_DECLARE_STRONG_TYPEDEF(
	sanguis::server::space_unit,
	range
);

}

#endif
