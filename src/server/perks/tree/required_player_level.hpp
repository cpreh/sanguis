#ifndef SANGUIS_SERVER_PERKS_TREE_REQUIRED_PLAYER_LEVEL_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_TREE_REQUIRED_PLAYER_LEVEL_HPP_INCLUDED

#include "../../level.hpp"
#include <fcppt/strong_typedef.hpp>

namespace sanguis
{
namespace server
{
namespace perks
{
namespace tree
{

FCPPT_MAKE_STRONG_TYPEDEF(
	server::level::value_type,
	required_player_level
);

}
}
}
}

#endif
