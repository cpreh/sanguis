#ifndef SANGUIS_SERVER_PERKS_TREE_CHOOSABLE_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_TREE_CHOOSABLE_HPP_INCLUDED

#include "object.hpp"
#include "../../level.hpp"
#include "../../../perk_type.hpp"

namespace sanguis
{
namespace server
{
namespace perks
{
namespace tree
{

bool
choosable(
	tree::object const &,
	sanguis::perk_type::type,
	server::level player_level
);

}
}
}
}

#endif
