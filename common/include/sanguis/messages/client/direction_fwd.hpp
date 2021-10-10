#ifndef SANGUIS_MESSAGES_CLIENT_DIRECTION_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_DIRECTION_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/vector2_fwd.hpp>
#include <sanguis/messages/client/types/make_message_id.hpp>
#include <sanguis/messages/client/types/message.hpp>
#include <sanguis/messages/roles/direction.hpp>
#include <alda/bindings/record_variadic_fwd.hpp>
#include <alda/message/object_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>

namespace sanguis::messages::client
{

using direction = alda::message::object<
    sanguis::messages::client::types::make_message_id<
        sanguis::messages::client::types::message::direction>,
    alda::bindings::record_variadic<fcppt::record::element<
        sanguis::messages::roles::direction,
        sanguis::messages::adapted_types::vector2>>>;

}

#endif
