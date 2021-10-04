#ifndef SANGUIS_SERVER_WEAPONS_IRS_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_IRS_HPP_INCLUDED

#include <sanguis/time_unit.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis::server::weapons
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::time_unit,
	irs
);

}

#endif
