#ifndef SANGUIS_SERVER_MESSAGE_EVENT_HPP_INCLUDED
#define SANGUIS_SERVER_MESSAGE_EVENT_HPP_INCLUDED

#include "../messages/auto_ptr.hpp"
#include "../messages/shared_ptr.hpp"
#include "../net/id_type.hpp"
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
	)
public:
	message_event(
		messages::auto_ptr message,
		net::id_type id
	);
	
	~message_event();
	
	messages::shared_ptr const
	message() const;

	net::id_type
	id() const;
private:
	messages::shared_ptr const message_;
	net::id_type const id_;
};

}
}

#endif
