#ifndef SANGUIS_SERVER_PERKS_TREE_CHOOSABLE_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_TREE_CHOOSABLE_HPP_INCLUDED

#include <sanguis/server/perks/tree/object.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/perk_type.hpp>

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
