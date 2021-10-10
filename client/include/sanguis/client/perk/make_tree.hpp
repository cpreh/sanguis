#ifndef SANGUIS_CLIENT_PERK_MAKE_TREE_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_MAKE_TREE_HPP_INCLUDED

#include <sanguis/client/perk/tree_unique_ptr.hpp>
#include <sanguis/messages/server/types/perk_tree_node_vector.hpp>

namespace sanguis::client::perk
{

sanguis::client::perk::tree_unique_ptr
make_tree(sanguis::messages::server::types::perk_tree_node_vector const &);

}

#endif
