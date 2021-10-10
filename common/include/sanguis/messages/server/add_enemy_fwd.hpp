#ifndef SANGUIS_MESSAGES_SERVER_ADD_ENEMY_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_ADD_ENEMY_FWD_HPP_INCLUDED

#include <sanguis/enemy_kind_fwd.hpp>
#include <sanguis/creator/enemy_type_fwd.hpp>
#include <sanguis/messages/adapted_types/enum_fwd.hpp>
#include <sanguis/messages/adapted_types/string_fwd.hpp>
#include <sanguis/messages/roles/enemy_kind.hpp>
#include <sanguis/messages/roles/enemy_type.hpp>
#include <sanguis/messages/roles/name.hpp>
#include <sanguis/messages/server/parts/add_actor_fwd.hpp>
#include <sanguis/messages/server/parts/entity_id_fwd.hpp>
#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/bindings/record_fwd.hpp>
#include <alda/message/object_fwd.hpp>
#include <fcppt/mpl/list/join.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/record/element_fwd.hpp>

namespace sanguis::messages::server
{

using add_enemy = alda::message::object<
    sanguis::messages::server::types::make_message_id<
        sanguis::messages::server::types::message::add_enemy>,
    alda::bindings::record<fcppt::mpl::list::join<fcppt::mpl::list::object<
        fcppt::mpl::list::object<sanguis::messages::server::parts::entity_id>,
        sanguis::messages::server::parts::add_actor,
        fcppt::mpl::list::object<
            fcppt::record::element<
                sanguis::messages::roles::enemy_type,
                sanguis::messages::adapted_types::enum_<sanguis::creator::enemy_type>>,
            fcppt::record::element<
                sanguis::messages::roles::enemy_kind,
                sanguis::messages::adapted_types::enum_<sanguis::enemy_kind>>,
            fcppt::record::element<
                sanguis::messages::roles::name,
                sanguis::messages::adapted_types::string>>>>>>;

}

#endif
