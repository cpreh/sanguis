#ifndef SANGUIS_CLIENT_PERK_CHOOSABLE_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_CHOOSABLE_HPP_INCLUDED

#include <sanguis/client/perk/choosable_state.hpp>
#include <sanguis/client/perk/level_map.hpp>
#include <sanguis/client/perk/tree.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/player_level.hpp>
#include <sanguis/perk_type.hpp>

namespace sanguis
{
namespace client
{
namespace perk
{

perk::choosable_state::type
choosable(
	sanguis::perk_type::type,
	perk::tree const &,
	perk::level_map const &,
	client::player_level,
	client::level perks_chosen
);

}
}
}

#endif
