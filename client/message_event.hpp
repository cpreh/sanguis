#ifndef SANGUIS_MESSAGE_EVENT_HPP_INCLUDED
#define SANGUIS_MESSAGE_EVENT_HPP_INCLUDED

#include "../messages/base.hpp"
#include <boost/statechart/event.hpp>

namespace sanguis
{
struct message_event : public boost::statechart::event<message_event> 
{
	const message_ptr message;
	message_event(const message_ptr message) : message(message) {}
};
}

#endif
