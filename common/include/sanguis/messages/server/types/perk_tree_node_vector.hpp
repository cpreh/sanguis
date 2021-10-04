#ifndef SANGUIS_MESSAGES_SERVER_TYPES_PERK_TREE_NODE_VECTOR_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_TYPES_PERK_TREE_NODE_VECTOR_HPP_INCLUDED

#include <sanguis/messages/server/types/perk_tree_node.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis::messages::server::types
{

using
perk_tree_node_vector
=
std::vector<
	sanguis::messages::server::types::perk_tree_node
>;

}

#endif
