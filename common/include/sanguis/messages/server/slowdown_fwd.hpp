#ifndef SANGUIS_MESSAGES_SERVER_SLOWDOWN_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_SLOWDOWN_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/space_unit_fwd.hpp>
#include <sanguis/messages/roles/slowdown.hpp>
#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/bindings/record_variadic_fwd.hpp>
#include <alda/message/object_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>

namespace sanguis::messages::server
{

using slowdown = alda::message::object<
    sanguis::messages::server::types::make_message_id<
        sanguis::messages::server::types::message::slowdown>,
    alda::bindings::record_variadic<fcppt::record::element<
        sanguis::messages::roles::slowdown,
        sanguis::messages::adapted_types::space_unit>>>;

}

#endif
