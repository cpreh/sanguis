#ifndef SANGUIS_MESSAGES_SERVER_ADD_AURA_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_ADD_AURA_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/aura_type_fwd.hpp>
#include <sanguis/messages/roles/aura_type.hpp>
#include <sanguis/messages/server/parts/entity_id_fwd.hpp>
#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/bindings/record_variadic_fwd.hpp>
#include <alda/message/object_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{

using
add_aura
=
alda::message::object<
	sanguis::messages::server::types::make_message_id<
		sanguis::messages::server::types::message::add_aura
	>,
	alda::bindings::record_variadic<
		sanguis::messages::server::parts::entity_id,
		fcppt::record::element<
			sanguis::messages::roles::aura_type,
			sanguis::messages::adapted_types::aura_type
		>
	>
>;

}
}
}

#endif
