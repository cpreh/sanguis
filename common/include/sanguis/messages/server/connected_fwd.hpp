#ifndef SANGUIS_MESSAGES_SERVER_CONNECTED_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_CONNECTED_FWD_HPP_INCLUDED

#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/bindings/unit_fwd.hpp>
#include <alda/message/object_fwd.hpp>

namespace sanguis::messages::server
{

using connected = alda::message::object<
    sanguis::messages::server::types::make_message_id<
        sanguis::messages::server::types::message::connected>,
    alda::bindings::unit>;

}

#endif
