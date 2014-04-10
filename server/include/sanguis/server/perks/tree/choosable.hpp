#ifndef SANGUIS_SERVER_PERKS_TREE_CHOOSABLE_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_TREE_CHOOSABLE_HPP_INCLUDED

#include <sanguis/perk_type_fwd.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/perks/tree/object_fwd.hpp>


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
	sanguis::server::perks::tree::object const &,
	sanguis::perk_type,
	sanguis::server::level player_level
);

}
}
}
}

#endif
