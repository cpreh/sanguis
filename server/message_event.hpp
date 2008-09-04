#ifndef SANGUIS_SERVER_MESSAGE_EVENT_HPP_INCLUDED
#define SANGUIS_SERVER_MESSAGE_EVENT_HPP_INCLUDED

#include "../messages/base.hpp"
#include "../net/types.hpp"
#include <boost/statechart/event.hpp>

namespace sanguis
{
namespace server
{

struct message_event : public boost::statechart::event<message_event> 
{
	messages::shared_ptr const message;
	net::id_type const id;

	message_event(
		messages::auto_ptr message,
		net::id_type id);
};
}
}

#endif
