#ifndef SANGUIS_MESSAGES_CLIENT_CHEAT_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_CHEAT_FWD_HPP_INCLUDED

#include <sanguis/cheat_type_fwd.hpp>
#include <sanguis/messages/adapted_types/enum_fwd.hpp>
#include <sanguis/messages/client/types/make_message_id.hpp>
#include <sanguis/messages/client/types/message.hpp>
#include <alda/message/object_fwd.hpp>


namespace sanguis::messages::client
{

using
cheat
=
alda::message::object<
	sanguis::messages::client::types::make_message_id<
		sanguis::messages::client::types::message::cheat
	>,
	sanguis::messages::adapted_types::enum_<
		sanguis::cheat_type
	>
>;

}

#endif
