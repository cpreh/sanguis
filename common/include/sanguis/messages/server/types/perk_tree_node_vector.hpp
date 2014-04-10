#ifndef SANGUIS_MESSAGES_SERVER_TYPES_PERK_TREE_NODE_VECTOR_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_TYPES_PERK_TREE_NODE_VECTOR_HPP_INCLUDED

#include <sanguis/messages/server/types/perk_tree_node.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{
namespace types
{

typedef
std::vector<
	sanguis::messages::server::types::perk_tree_node
>
perk_tree_node_vector;

}
}
}
}

#endif
