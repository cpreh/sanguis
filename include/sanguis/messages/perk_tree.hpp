#ifndef SANGUIS_MESSAGES_PERK_TREE_HPP_INCLUDED
#define SANGUIS_MESSAGES_PERK_TREE_HPP_INCLUDED

#include <sanguis/messages/perk_tree_node_list.hpp>
#include <sanguis/messages/perk_tree_node.hpp>
#include <sanguis/messages/bindings/dynamic_len.hpp>
#include <sanguis/messages/bindings/self.hpp>

namespace sanguis
{
namespace messages
{

typedef bindings::dynamic_len<
	messages::perk_tree_node_list,
	bindings::self<
		messages::perk_tree_node
	>
> perk_tree;

}
}

#endif
