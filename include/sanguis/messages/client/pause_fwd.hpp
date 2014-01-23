#ifndef SANGUIS_MESSAGES_CLIENT_PAUSE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_PAUSE_FWD_HPP_INCLUDED

#include <sanguis/messages/client/types/make_message_id_fwd.hpp>
#include <sanguis/messages/client/types/message.hpp>
#include <alda/message/make_class_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace client
{

typedef
alda::message::make_class<
	sanguis::messages::client::types::make_message_id<
		sanguis::messages::client::types::message::pause
	>
>
pause;

}
}
}

#endif
