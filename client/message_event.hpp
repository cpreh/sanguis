#ifndef SANGUIS_CLIENT_MESSAGE_EVENT_HPP_INCLUDED
#define SANGUIS_CLIENT_MESSAGE_EVENT_HPP_INCLUDED

#include "../messages/base.hpp"
#include <boost/statechart/event.hpp>

namespace sanguis
{
namespace client
{

struct message_event : public boost::statechart::event<message_event> {
	messages::shared_ptr message;
	explicit message_event(
		messages::auto_ptr message);
};

}
}

#endif
