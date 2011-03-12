#include "message.hpp"
#include "../../messages/base.hpp"

sanguis::client::events::message::message(
	messages::auto_ptr _value
)
:
	value_(
		_value.release()
	)
{}

sanguis::client::events::message::~message()
{}

sanguis::messages::shared_ptr const
sanguis::client::events::message::value() const
{
	return value_;
}
