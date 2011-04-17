#ifndef SANGUIS_MESSAGES_PERK_TREE_NODE_HPP_INCLUDED
#define SANGUIS_MESSAGES_PERK_TREE_NODE_HPP_INCLUDED

#include "perk_list.hpp"
#include "enum.hpp"
#include "roles/perk_children.hpp"
#include "roles/perk_label.hpp"
#include "make_class.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace messages
{

typedef messages::make_class<
	majutsu::composite<
		boost::mpl::vector2<
			majutsu::role<
				messages::enum_,
				roles::perk_label
			>,
			majutsu::role<
				messages::perk_list,
				roles::perk_children
			>
		>
	>
>::type perk_tree_node;

}
}

#endif
