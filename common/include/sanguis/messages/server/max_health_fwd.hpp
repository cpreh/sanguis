#ifndef SANGUIS_MESSAGES_SERVER_MAX_HEALTH_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_MAX_HEALTH_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/space_unit_fwd.hpp>
#include <sanguis/messages/roles/max_health.hpp>
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

typedef
alda::message::object<
	sanguis::messages::server::types::make_message_id<
		sanguis::messages::server::types::message::max_health
	>,
	alda::bindings::record_variadic<
		sanguis::messages::server::parts::entity_id,
		fcppt::record::element<
			sanguis::messages::roles::max_health,
			sanguis::messages::adapted_types::space_unit
		>
	>
>
max_health;

}
}
}

#endif
