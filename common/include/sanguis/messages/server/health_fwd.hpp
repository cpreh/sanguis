#ifndef SANGUIS_MESSAGES_SERVER_HEALTH_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_HEALTH_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/space_unit_fwd.hpp>
#include <sanguis/messages/roles/health.hpp>
#include <sanguis/messages/server/parts/entity_id_fwd.hpp>
#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/message/record_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{

typedef
alda::message::record<
	sanguis::messages::server::types::make_message_id<
		sanguis::messages::server::types::message::health
	>,
	boost::mpl::vector2<
		sanguis::messages::server::parts::entity_id,
		fcppt::record::element<
			sanguis::messages::roles::health,
			sanguis::messages::adapted_types::space_unit
		>
	>
>
health;

}
}
}

#endif
