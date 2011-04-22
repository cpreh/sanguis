#ifndef SANGUIS_CLIENT_PERK_CHOOSABLE_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_CHOOSABLE_HPP_INCLUDED

#include "choosable_state.hpp"
#include "level_map.hpp"
#include "tree.hpp"
#include "../level.hpp"
#include "../../perk_type.hpp"

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
	perk::level_map &,
	client::level player_level
);

}
}
}

#endif
