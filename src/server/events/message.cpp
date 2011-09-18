#include <sanguis/server/events/message.hpp>
#include <sanguis/messages/base.hpp>

sanguis::server::events::message::message(
	messages::auto_ptr _message,
	net::id const _id
)
:
	message_(
		// TODO: this is not safe!
		_message.release()
	),
	id_(_id)
{
}

sanguis::server::events::message::~message()
{
}

sanguis::messages::shared_ptr const
sanguis::server::events::message::get() const
{
	return message_;
}

sanguis::net::id
sanguis::server::events::message::id() const
{
	return id_;
}
