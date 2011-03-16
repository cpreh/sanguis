#ifndef SANGUIS_SERVER_MESSAGE_EVENT_HPP_INCLUDED
#define SANGUIS_SERVER_MESSAGE_EVENT_HPP_INCLUDED

#include "../messages/auto_ptr.hpp"
#include "../messages/shared_ptr.hpp"
#include "../net/id.hpp"
#include <fcppt/nonassignable.hpp>
#include <boost/statechart/event.hpp>

namespace sanguis
{
namespace server
{

class message_event
:
	public boost::statechart::event<
		message_event
	>
{
	FCPPT_NONASSIGNABLE(
		message_event
	);
public:
	message_event(
		messages::auto_ptr,
		net::id
	);
	
	~message_event();
	
	messages::shared_ptr const
	message() const;

	net::id
	id() const;
private:
	messages::shared_ptr const message_;

	net::id const id_;
};

}
}

#endif
