#ifndef SANGUIS_MESSAGES_SERVER_SPEED_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_SPEED_FWD_HPP_INCLUDED

#include <sanguis/messages/server/parts/entity_id_fwd.hpp>
#include <sanguis/messages/server/parts/speed_fwd.hpp>
#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/bindings/record_variadic_fwd.hpp>
#include <alda/message/object_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>

namespace sanguis::messages::server
{

using speed = alda::message::object<
    sanguis::messages::server::types::make_message_id<
        sanguis::messages::server::types::message::speed>,
    alda::bindings::record_variadic<
        sanguis::messages::server::parts::entity_id,
        sanguis::messages::server::parts::speed>>;

}

#endif
