#include <sanguis/client/events/message.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/messages/shared_ptr.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::events::message::message(
	sanguis::messages::unique_ptr &&_value
)
:
	value_(
		std::move(
			_value
		)
	)
{
}

sanguis::client::events::message::~message()
{
}

sanguis::messages::shared_ptr const
sanguis::client::events::message::value() const
{
	return
		value_;
}
