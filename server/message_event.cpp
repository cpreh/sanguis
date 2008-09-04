#include "message_event.hpp"

sanguis::server::message_event::message_event(
	messages::auto_ptr message,
	net::id_type const id) 
: message(message),
  id(id) 
{}
