#ifndef SANGUIS_MESSAGES_SERVER_TYPES_PERK_TREE_NODE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_TYPES_PERK_TREE_NODE_FWD_HPP_INCLUDED

#include <sanguis/messages/server/adapted_types/perk_tree_node_fwd.hpp>
#include <alda/bindings/enum_decl.hpp>
#include <alda/bindings/optional_decl.hpp>
#include <alda/bindings/record_variadic_decl.hpp>
#include <alda/bindings/strong_typedef_decl.hpp>
#include <alda/raw/element_type.hpp>


namespace sanguis::messages::server::types
{

using
perk_tree_node
=
alda::raw::element_type<
	sanguis::messages::server::adapted_types::perk_tree_node
>;

}

#endif
