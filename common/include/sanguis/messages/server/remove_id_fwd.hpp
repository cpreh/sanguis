#ifndef SANGUIS_MESSAGES_SERVER_REMOVE_ID_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_REMOVE_ID_FWD_HPP_INCLUDED

#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/bindings/unit_fwd.hpp>
#include <alda/message/object_fwd.hpp>

namespace sanguis::messages::server
{

using remove_id = alda::message::object<
    sanguis::messages::server::types::make_message_id<
        sanguis::messages::server::types::message::remove_id>,
    alda::bindings::unit>;

}

#endif
