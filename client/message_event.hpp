#ifndef SANGUIS_CLIENT_MESSAGE_EVENT_HPP_INCLUDED
#define SANGUIS_CLIENT_MESSAGE_EVENT_HPP_INCLUDED

#include "../messages/auto_ptr.hpp"
#include "../messages/shared_ptr.hpp"
#include <boost/statechart/event.hpp>

namespace sanguis
{
namespace client
{

struct message_event : public boost::statechart::event<message_event> {
	explicit message_event(
		messages::auto_ptr message);
	
	~message_event();

	messages::shared_ptr const
	message();
private:
	messages::shared_ptr message_;
};

}
}

#endif
