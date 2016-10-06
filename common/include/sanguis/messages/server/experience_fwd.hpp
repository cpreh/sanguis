#ifndef SANGUIS_MESSAGES_SERVER_EXPERIENCE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_EXPERIENCE_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/exp_fwd.hpp>
#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/message/object_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{

typedef
alda::message::object<
	sanguis::messages::server::types::make_message_id<
		sanguis::messages::server::types::message::experience
	>,
	sanguis::messages::adapted_types::exp
>
experience;

}
}
}

#endif
