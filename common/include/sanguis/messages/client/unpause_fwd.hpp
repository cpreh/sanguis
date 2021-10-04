#ifndef SANGUIS_MESSAGES_CLIENT_UNPAUSE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_UNPAUSE_FWD_HPP_INCLUDED

#include <sanguis/messages/client/types/make_message_id.hpp>
#include <sanguis/messages/client/types/message.hpp>
#include <alda/bindings/unit_fwd.hpp>
#include <alda/message/object_fwd.hpp>


namespace sanguis::messages::client
{

using
unpause
=
alda::message::object<
	sanguis::messages::client::types::make_message_id<
		sanguis::messages::client::types::message::unpause
	>,
	alda::bindings::unit
>;

}

#endif
