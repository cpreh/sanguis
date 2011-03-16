#include "message_event.hpp"
#include "../messages/base.hpp"

sanguis::server::message_event::message_event(
	messages::auto_ptr _message,
	net::id const _id
)
:
	message_(
		_message.release()
	),
	id_(_id) 
{}

sanguis::server::message_event::~message_event()
{
}

sanguis::messages::shared_ptr const
sanguis::server::message_event::message() const
{
	return message_;
}

sanguis::net::id
sanguis::server::message_event::id() const
{
	return id_;
}
