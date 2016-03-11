#ifndef SANGUIS_MESSAGES_CLIENT_TYPES_MAKE_MESSAGE_ID_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_TYPES_MAKE_MESSAGE_ID_HPP_INCLUDED

#include <sanguis/messages/client/types/alda_type.hpp>
#include <sanguis/messages/client/types/message_fwd.hpp>
#include <alda/message/make_id.hpp>


namespace sanguis
{
namespace messages
{
namespace client
{
namespace types
{

template<
	sanguis::messages::client::types::message Msg
>
using make_message_id
=
alda::message::make_id<
	sanguis::messages::client::types::alda_type,
	Msg
>;

}
}
}
}

#endif
