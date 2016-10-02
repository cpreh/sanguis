#ifndef SANGUIS_MESSAGES_SERVER_LEVEL_UP_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_LEVEL_UP_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/exp_fwd.hpp>
#include <sanguis/messages/adapted_types/level_fwd.hpp>
#include <sanguis/messages/roles/exp_for_next_level.hpp>
#include <sanguis/messages/roles/level.hpp>
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
		sanguis::messages::server::types::message::level_up
	>,
	boost::mpl::vector2<
		fcppt::record::element<
			sanguis::messages::roles::level,
			sanguis::messages::adapted_types::level
		>,
		fcppt::record::element<
			sanguis::messages::roles::exp_for_next_level,
			sanguis::messages::adapted_types::exp
		>
	>
>
level_up;

}
}
}

#endif
