#ifndef SANGUIS_MESSAGES_SERVER_ADD_WEAPON_PICKUP_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_ADD_WEAPON_PICKUP_FWD_HPP_INCLUDED

#include <sanguis/messages/server/parts/add_elements_base_fwd.hpp>
#include <sanguis/messages/server/parts/entity_id_fwd.hpp>
#include <sanguis/messages/server/parts/weapon_description_fwd.hpp>
#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/bindings/record_fwd.hpp>
#include <alda/message/object_fwd.hpp>
#include <fcppt/mpl/list/join.hpp>
#include <fcppt/mpl/list/object.hpp>

namespace sanguis::messages::server
{

using add_weapon_pickup = alda::message::object<
    sanguis::messages::server::types::make_message_id<
        sanguis::messages::server::types::message::add_weapon_pickup>,
    alda::bindings::record<fcppt::mpl::list::join<fcppt::mpl::list::object<
        fcppt::mpl::list::object<sanguis::messages::server::parts::entity_id>,
        sanguis::messages::server::parts::add_elements_base,
        sanguis::messages::server::parts::weapon_description>>>>;

}

#endif
