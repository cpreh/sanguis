#include "message_event.hpp"

sanguis::server::message_event::message_event(
	messages::auto_ptr message_,
	net::id_type const id_) 
:
	message_(message_),
	id_(id_) 
{}

sanguis::server::message_event::~message_event()
{}

sanguis::messages::shared_ptr const
sanguis::server::message_event::message() const
{
	return message_;
}

sanguis::net::id_type
sanguis::server::message_event::id() const
{
	return id_;
}
