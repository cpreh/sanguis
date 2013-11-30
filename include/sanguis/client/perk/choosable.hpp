#ifndef SANGUIS_CLIENT_PERK_CHOOSABLE_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_CHOOSABLE_HPP_INCLUDED

#include <sanguis/perk_type_fwd.hpp>
#include <sanguis/client/player_level.hpp>
#include <sanguis/client/perk/choosable_state_fwd.hpp>
#include <sanguis/client/perk/remaining_levels.hpp>
#include <sanguis/client/perk/tree_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace perk
{

sanguis::client::perk::choosable_state
choosable(
	sanguis::perk_type,
	sanguis::client::perk::tree const &,
	sanguis::client::player_level,
	sanguis::client::perk::remaining_levels
);

}
}
}

#endif
