#include <sanguis/server/player_id.hpp>
#include <sanguis/server/events/message.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/messages/shared_ptr.hpp>


sanguis::server::events::message::message(
	sanguis::messages::auto_ptr _message,
	sanguis::server::player_id const _id
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

sanguis::server::player_id const
sanguis::server::events::message::id() const
{
	return id_;
}
