#include "message_event.hpp"

sanguis::server::message_event::message_event(
	const message_ptr message,
	const net::id_type id) 
: message(message),
  id(id) 
{}
