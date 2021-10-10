#ifndef SANGUIS_SERVER_PERKS_TREE_CHOOSE_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_TREE_CHOOSE_HPP_INCLUDED

#include <sanguis/perk_type_fwd.hpp>
#include <sanguis/server/perks/tree/container.hpp>

namespace sanguis::server::perks::tree
{

void choose(
    sanguis::server::perks::tree::container &, // NOLINT(google-runtime-references)
    sanguis::perk_type);

}

#endif
