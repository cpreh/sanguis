#ifndef SANGUIS_SERVER_PERKS_TREE_REQUIRED_PLAYER_LEVEL_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_TREE_REQUIRED_PLAYER_LEVEL_HPP_INCLUDED

#include <sanguis/server/level.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis::server::perks::tree
{

FCPPT_DECLARE_STRONG_TYPEDEF(
	sanguis::server::level::value_type,
	required_player_level
);

}

#endif
