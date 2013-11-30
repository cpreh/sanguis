#ifndef SANGUIS_MESSAGES_AVAILABLE_PERKS_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_AVAILABLE_PERKS_FWD_HPP_INCLUDED

#include <sanguis/messages/bind_entity_message_fwd.hpp>
#include <sanguis/messages/make_class_fwd.hpp>
#include <sanguis/messages/perk_tree_fwd.hpp>
#include <sanguis/messages/adapted_types/level_fwd.hpp>
#include <sanguis/messages/roles/remaining_perk_levels.hpp>
#include <sanguis/messages/types/message.hpp>
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
		boost::mpl::vector3<
			sanguis::messages::bind_entity_message<
				sanguis::messages::types::message::available_perks
			>,
			majutsu::role<
				sanguis::messages::perk_tree
			>,
			majutsu::role<
				sanguis::messages::adapted_types::level,
				sanguis::messages::roles::remaining_perk_levels
			>
		>
	>
>
available_perks;

}
}

#endif
