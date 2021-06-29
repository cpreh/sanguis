#ifndef SANGUIS_MESSAGES_SERVER_ADD_DESTRUCTIBLE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_ADD_DESTRUCTIBLE_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/destructible_type_fwd.hpp>
#include <sanguis/messages/roles/destructible_type.hpp>
#include <sanguis/messages/server/parts/add_elements_base_fwd.hpp>
#include <sanguis/messages/server/parts/entity_id_fwd.hpp>
#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/bindings/record_fwd.hpp>
#include <alda/message/object_fwd.hpp>
#include <fcppt/mpl/list/join.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/record/element_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{

using
add_destructible
=
alda::message::object<
	sanguis::messages::server::types::make_message_id<
		sanguis::messages::server::types::message::add_destructible
	>,
	alda::bindings::record<
		fcppt::mpl::list::join<
			fcppt::mpl::list::object<
				fcppt::mpl::list::object<
					sanguis::messages::server::parts::entity_id
				>,
				sanguis::messages::server::parts::add_elements_base,
				fcppt::mpl::list::object<
					fcppt::record::element<
						sanguis::messages::roles::destructible_type,
						sanguis::messages::adapted_types::destructible_type
					>
				>
			>
		>
	>
>;

}
}
}

#endif
