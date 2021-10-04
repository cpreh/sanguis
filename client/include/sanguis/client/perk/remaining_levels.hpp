#ifndef SANGUIS_CLIENT_PERK_REMAINING_LEVELS_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_REMAINING_LEVELS_HPP_INCLUDED

#include <sanguis/client/level.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis::client::perk
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::client::level,
	remaining_levels
);

}

#endif
