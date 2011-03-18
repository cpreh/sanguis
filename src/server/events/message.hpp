#ifndef SANGUIS_SERVER_EVENTS_MESSAGE_HPP_INCLUDED
#define SANGUIS_SERVER_EVENTS_MESSAGE_HPP_INCLUDED

#include "message_fwd.hpp"
#include "../../messages/auto_ptr.hpp"
#include "../../messages/shared_ptr.hpp"
#include "../../net/id.hpp"
#include <fcppt/nonassignable.hpp>
#include <boost/statechart/event.hpp>

namespace sanguis
{
namespace server
{
namespace events
{

class message
:
	public boost::statechart::event<
		message
	>
{
	FCPPT_NONASSIGNABLE(
		message
	);
public:
	message(
		messages::auto_ptr,
		net::id
	);
	
	~message();
	
	messages::shared_ptr const
	get() const;

	net::id
	id() const;
private:
	messages::shared_ptr const message_;

	net::id const id_;
};

}
}
}

#endif
