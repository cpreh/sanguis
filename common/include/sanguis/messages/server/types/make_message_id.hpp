#ifndef SANGUIS_MESSAGES_SERVER_TYPES_MAKE_MESSAGE_ID_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_TYPES_MAKE_MESSAGE_ID_HPP_INCLUDED

#include <sanguis/messages/server/types/alda_type.hpp>
#include <sanguis/messages/server/types/message_fwd.hpp>
#include <alda/message/make_id.hpp>

namespace sanguis::messages::server::types
{

template <sanguis::messages::server::types::message Msg>
using make_message_id = alda::message::make_id<sanguis::messages::server::types::alda_type, Msg>;

}

#endif
