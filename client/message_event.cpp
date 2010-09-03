#include "message_event.hpp"
#include "../messages/base.hpp"

sanguis::client::message_event::message_event(
	messages::auto_ptr _message
)
:
	message_(
		_message.release()
	)
{}

sanguis::client::message_event::~message_event()
{}

sanguis::messages::shared_ptr const
sanguis::client::message_event::message() const
{
	return message_;
}
