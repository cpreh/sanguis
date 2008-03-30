#ifndef SANGUIS_MESSAGE_EVENT_HPP_INCLUDED
#define SANGUIS_MESSAGE_EVENT_HPP_INCLUDED

#include "../messages/base.hpp"
#include "../net/types.hpp"
#include <sge/iostream.hpp>
#include <boost/statechart/event.hpp>

namespace sanguis
{
struct message_event : public boost::statechart::event<message_event> 
{
	message_ptr message;
	net::id_type id;

	message_event(const message_ptr message,const net::id_type id) 
		: message(message),id(id) 
	{
		sge::cerr << "server: message_event constructor\n";
	}

	message_event(const message_event &m)
	{
		sge::cerr << "server: message_event copyconstructor\n";
		id = m.id;
		message = m.message;
	}

	boost::intrusive_ptr<const boost::statechart::event_base> clone() const
	{
		sge::cerr << "server: in event::clone()\n";
		return boost::intrusive_ptr<const boost::statechart::event_base>(new message_event(*this));
	}
};
}

#endif
