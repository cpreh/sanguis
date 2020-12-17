#ifndef SANGUIS_MESSAGES_SERVER_UNPAUSE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_UNPAUSE_FWD_HPP_INCLUDED

#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/bindings/unit_fwd.hpp>
#include <alda/message/object_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{

using
unpause
=
alda::message::object<
	sanguis::messages::server::types::make_message_id<
		sanguis::messages::server::types::message::unpause
	>,
	alda::bindings::unit
>;

}
}
}

#endif
