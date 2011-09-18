#ifndef SANGUIS_MESSAGES_PERK_TREE_NODE_LIST_HPP_INCLUDED
#define SANGUIS_MESSAGES_PERK_TREE_NODE_LIST_HPP_INCLUDED

#include <sanguis/messages/perk_tree_node.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace messages
{

typedef std::vector<
	messages::perk_tree_node
> perk_tree_node_list;

}
}

#endif
