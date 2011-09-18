#ifndef SANGUIS_MESSAGES_PERK_TREE_NODE_HPP_INCLUDED
#define SANGUIS_MESSAGES_PERK_TREE_NODE_HPP_INCLUDED

#include <sanguis/messages/enum.hpp>
#include <sanguis/messages/level.hpp>
#include <sanguis/messages/make_class.hpp>
#include <sanguis/messages/perk_list.hpp>
#include <sanguis/messages/roles/max_perk_level.hpp>
#include <sanguis/messages/roles/perk_children.hpp>
#include <sanguis/messages/roles/perk_label.hpp>
#include <sanguis/messages/roles/required_perk_parent_level.hpp>
#include <sanguis/messages/roles/required_perk_player_level.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace messages
{

typedef messages::make_class<
	majutsu::composite<
		boost::mpl::vector5<
			majutsu::role<
				messages::enum_,
				roles::perk_label
			>,
			majutsu::role<
				messages::level,
				roles::required_perk_player_level
			>,
			majutsu::role<
				messages::level,
				roles::required_perk_parent_level
			>,
			majutsu::role<
				messages::level,
				roles::max_perk_level
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
