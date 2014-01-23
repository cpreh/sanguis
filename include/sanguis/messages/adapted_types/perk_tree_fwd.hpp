#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_PERK_TREE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_PERK_TREE_FWD_HPP_INCLUDED

#include <sanguis/messages/server/types/perk_tree_node_fwd.hpp>
#include <sanguis/messages/server/types/perk_tree_node_vector.hpp>
#include <alda/bindings/class_fwd.hpp>
#include <alda/bindings/dynamic_len_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace adapted_types
{

typedef
alda::bindings::dynamic_len<
	sanguis::messages::server::types::perk_tree_node_vector,
	alda::bindings::class_<
		sanguis::messages::server::types::perk_tree_node
	>
>
perk_tree;

}
}
}

#endif
