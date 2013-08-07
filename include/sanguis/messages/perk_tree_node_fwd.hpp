#ifndef SANGUIS_MESSAGES_PERK_TREE_NODE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_PERK_TREE_NODE_FWD_HPP_INCLUDED

#include <sanguis/perk_type_fwd.hpp>
#include <sanguis/messages/enum_fwd.hpp>
#include <sanguis/messages/level_fwd.hpp>
#include <sanguis/messages/make_class_fwd.hpp>
#include <sanguis/messages/roles/max_perk_level.hpp>
#include <sanguis/messages/roles/perk_parent.hpp>
#include <sanguis/messages/roles/perk_label.hpp>
#include <sanguis/messages/roles/required_perk_parent_level.hpp>
#include <sanguis/messages/roles/required_perk_player_level.hpp>
#include <alda/bindings/optional_fwd.hpp>
#include <majutsu/composite_fwd.hpp>
#include <majutsu/role_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{

typedef
sanguis::messages::make_class<
	majutsu::composite<
		boost::mpl::vector5<
			majutsu::role<
				sanguis::messages::enum_<
					sanguis::perk_type
				>,
				sanguis::messages::roles::perk_label
			>,
			majutsu::role<
				sanguis::messages::level,
				sanguis::messages::roles::required_perk_player_level
			>,
			majutsu::role<
				sanguis::messages::level,
				sanguis::messages::roles::required_perk_parent_level
			>,
			majutsu::role<
				sanguis::messages::level,
				sanguis::messages::roles::max_perk_level
			>,
			majutsu::role<
				alda::bindings::optional<
					sanguis::perk_type,
					sanguis::messages::enum_<
						sanguis::perk_type
					>
				>,
				sanguis::messages::roles::perk_parent
			>
		>
	>
>
perk_tree_node;

}
}

#endif
