#ifndef SANGUIS_MESSAGES_SERVER_ADD_OWN_PLAYER_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_ADD_OWN_PLAYER_FWD_HPP_INCLUDED

#include <sanguis/messages/server/parts/add_player_fwd.hpp>
#include <sanguis/messages/server/parts/entity_id_fwd.hpp>
#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/bindings/record_fwd.hpp>
#include <alda/message/object_fwd.hpp>
#include <fcppt/mpl/list/append.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/record/element_fwd.hpp>

namespace sanguis::messages::server
{

using add_own_player = alda::message::object<
    sanguis::messages::server::types::make_message_id<
        sanguis::messages::server::types::message::add_own_player>,
    alda::bindings::record<fcppt::mpl::list::append<
        fcppt::mpl::list::object<sanguis::messages::server::parts::entity_id>,
        sanguis::messages::server::parts::add_player>>>;

}

#endif
