#ifndef SANGUIS_MESSAGES_SERVER_AVAILABLE_PERKS_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_AVAILABLE_PERKS_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/level_fwd.hpp>
#include <sanguis/messages/adapted_types/perk_tree_fwd.hpp>
#include <sanguis/messages/roles/perk_tree.hpp>
#include <sanguis/messages/roles/remaining_perk_levels.hpp>
#include <sanguis/messages/server/types/make_message_id_fwd.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/message/make_class_fwd.hpp>
#include <majutsu/composite_fwd.hpp>
#include <majutsu/role_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{

typedef
alda::message::make_class<
	majutsu::composite<
		boost::mpl::vector3<
			sanguis::messages::server::types::make_message_id<
				sanguis::messages::server::types::message::available_perks
			>,
			majutsu::role<
				sanguis::messages::adapted_types::perk_tree,
				sanguis::messages::roles::perk_tree
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
}

#endif
