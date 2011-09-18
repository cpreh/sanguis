#include <sanguis/client/events/net_error.hpp>

sanguis::client::events::net_error::net_error(
	fcppt::string const &_message,
	boost::system::error_code const &_code
)
:
	message_(_message),
	code_(_code)
{
}

fcppt::string const &
sanguis::client::events::net_error::message() const
{
	return message_;
}

boost::system::error_code const &
sanguis::client::events::net_error::code() const
{
	return code_;
}
