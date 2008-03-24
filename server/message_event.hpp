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
		sge::cout << "constructed message with id " << id << "\n";
	}

	message_event(const message_event &m)
	{
		sge::cout << "copy-constructed message with id " << m.id << "\n";
		message = m.message;
		id = m.id;
	}

	message_event &operator=(const message_event &r)
	{
		sge::cout << "assigning with " << r.id << "\n";
		return *this;
	}
};
}

#endif
