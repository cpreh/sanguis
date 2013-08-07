#ifndef SANGUIS_MESSAGES_PERK_TREE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_PERK_TREE_FWD_HPP_INCLUDED

#include <sanguis/messages/perk_tree_node_list.hpp>
#include <sanguis/messages/perk_tree_node_fwd.hpp>
#include <sanguis/messages/bindings/self_fwd.hpp>
#include <alda/bindings/dynamic_len_fwd.hpp>


namespace sanguis
{
namespace messages
{

// TODO: We should be able to fwd perk_tree_node_list!
typedef alda::bindings::dynamic_len<
	sanguis::messages::perk_tree_node_list,
	sanguis::messages::bindings::self<
		sanguis::messages::perk_tree_node
	>
> perk_tree;

}
}

#endif
