#ifndef SANGUIS_MESSAGES_SERVER_REMOVE_BUFF_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_REMOVE_BUFF_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/buff_type_fwd.hpp>
#include <sanguis/messages/roles/buff_type.hpp>
#include <sanguis/messages/server/parts/entity_id_fwd.hpp>
#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/bindings/record_variadic_fwd.hpp>
#include <alda/message/object_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>

namespace sanguis::messages::server
{

using remove_buff = alda::message::object<
    sanguis::messages::server::types::make_message_id<
        sanguis::messages::server::types::message::remove_buff>,
    alda::bindings::record_variadic<
        sanguis::messages::server::parts::entity_id,
        fcppt::record::element<
            sanguis::messages::roles::buff_type,
            sanguis::messages::adapted_types::buff_type>>>;

}

#endif
