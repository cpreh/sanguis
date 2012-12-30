#ifndef SANGUIS_CLIENT_PERK_CHOOSABLE_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_CHOOSABLE_HPP_INCLUDED

#include <sanguis/perk_type_fwd.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/player_level.hpp>
#include <sanguis/client/perk/choosable_state.hpp>
#include <sanguis/client/perk/level_map.hpp>
#include <sanguis/client/perk/tree.hpp>


namespace sanguis
{
namespace client
{
namespace perk
{

sanguis::client::perk::choosable_state::type
choosable(
	sanguis::perk_type,
	sanguis::client::perk::tree const &,
	sanguis::client::perk::level_map const &,
	sanguis::client::player_level,
	sanguis::client::level perks_chosen
);

}
}
}

#endif
