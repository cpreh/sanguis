#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_PERK_TREE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_PERK_TREE_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/dynamic_len_fwd.hpp>
#include <sanguis/messages/server/adapted_types/perk_tree_node_fwd.hpp>
#include <sanguis/messages/server/types/perk_tree_node_vector.hpp>

namespace sanguis::messages::adapted_types
{

using perk_tree = sanguis::messages::adapted_types::dynamic_len<
    sanguis::messages::server::types::perk_tree_node_vector,
    sanguis::messages::server::adapted_types::perk_tree_node>;

}

#endif
