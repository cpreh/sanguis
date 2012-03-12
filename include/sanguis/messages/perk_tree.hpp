#ifndef SANGUIS_MESSAGES_PERK_TREE_HPP_INCLUDED
#define SANGUIS_MESSAGES_PERK_TREE_HPP_INCLUDED

#include <sanguis/messages/perk_tree_node_list.hpp>
#include <sanguis/messages/perk_tree_node.hpp>
#include <sanguis/messages/bindings/self.hpp>
#include <alda/bindings/dynamic_len.hpp>


namespace sanguis
{
namespace messages
{

typedef alda::bindings::dynamic_len<
	sanguis::messages::perk_tree_node_list,
	sanguis::messages::bindings::self<
		sanguis::messages::perk_tree_node
	>
> perk_tree;

}
}

#endif
