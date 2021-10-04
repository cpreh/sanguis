#ifndef SANGUIS_MESSAGES_CLIENT_CHOOSE_PERK_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_CHOOSE_PERK_FWD_HPP_INCLUDED

#include <sanguis/perk_type_fwd.hpp>
#include <sanguis/messages/adapted_types/enum_fwd.hpp>
#include <sanguis/messages/client/types/make_message_id.hpp>
#include <sanguis/messages/client/types/message.hpp>
#include <alda/message/object_fwd.hpp>


namespace sanguis::messages::client
{

using
choose_perk
=
alda::message::object<
	sanguis::messages::client::types::make_message_id<
		sanguis::messages::client::types::message::choose_perk
	>,
	sanguis::messages::adapted_types::enum_<
		sanguis::perk_type
	>
>;

}

#endif
