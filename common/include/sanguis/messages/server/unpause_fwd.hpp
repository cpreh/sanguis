#ifndef SANGUIS_MESSAGES_SERVER_UNPAUSE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_UNPAUSE_FWD_HPP_INCLUDED

#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/message/record_fwd.hpp>
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
		sanguis::messages::server::types::message::unpause
	>,
	boost::mpl::vector0<>
>
unpause;

}
}
}

#endif
