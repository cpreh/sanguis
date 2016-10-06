#ifndef SANGUIS_MESSAGES_SERVER_AVAILABLE_PERKS_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_AVAILABLE_PERKS_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/level_fwd.hpp>
#include <sanguis/messages/adapted_types/perk_tree_fwd.hpp>
#include <sanguis/messages/roles/perk_tree.hpp>
#include <sanguis/messages/roles/remaining_perk_levels.hpp>
#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/bindings/record_variadic_fwd.hpp>
#include <alda/message/object_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{

typedef
alda::message::object<
	sanguis::messages::server::types::make_message_id<
		sanguis::messages::server::types::message::available_perks
	>,
	alda::bindings::record_variadic<
		fcppt::record::element<
			sanguis::messages::roles::perk_tree,
			sanguis::messages::adapted_types::perk_tree
		>,
		fcppt::record::element<
			sanguis::messages::roles::remaining_perk_levels,
			sanguis::messages::adapted_types::level
		>
	>
>
available_perks;

}
}
}

#endif
