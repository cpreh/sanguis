#ifndef SANGUIS_SERVER_PERKS_TREE_MAX_LEVEL_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_TREE_MAX_LEVEL_HPP_INCLUDED

#include <sanguis/server/level.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis::server::perks::tree
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::server::level::value_type,
	max_level
);

}

#endif
