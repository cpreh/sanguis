#ifndef SANGUIS_MESSAGES_SERVER_PAUSE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PAUSE_FWD_HPP_INCLUDED

#include <sanguis/messages/server/types/make_message_id_fwd.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/message/make_class_fwd.hpp>
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
alda::message::make_class<
	boost::mpl::vector1<
		sanguis::messages::server::types::make_message_id<
			sanguis::messages::server::types::message::pause
		>
	>
>
pause;

}
}
}

#endif
