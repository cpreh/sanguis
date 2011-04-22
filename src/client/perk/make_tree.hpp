#ifndef SANGUIS_CLIENT_PERK_MAKE_TREE_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_MAKE_TREE_HPP_INCLUDED

#include "tree_unique_ptr.hpp"
#include "../../messages/perk_tree_node_list.hpp"

namespace sanguis
{
namespace client
{
namespace perk
{

perk::tree_unique_ptr
make_tree(
	messages::perk_tree_node_list const &
);

}
}
}

#endif