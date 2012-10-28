#include <sanguis/server/events/message.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/messages/shared_ptr.hpp>
#include <alda/net/id.hpp>


sanguis::server::events::message::message(
	sanguis::messages::auto_ptr _message,
	alda::net::id const _id
)
:
	message_(
		// TODO: this is not safe!
		_message.release()
	),
	id_(
		_id
	)
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

alda::net::id const
sanguis::server::events::message::id() const
{
	return id_;
}
