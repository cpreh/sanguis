#include <sanguis/client/events/net_error.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/system/error_code.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::client::events::net_error::net_error(
	fcppt::string const &_message,
	boost::system::error_code const &_code
)
:
	message_(
		_message
	),
	code_(
		_code
	)
{
}

sanguis::client::events::net_error::net_error(
	net_error &&
)
= default;

sanguis::client::events::net_error::net_error(
	net_error const &
)
= default;

sanguis::client::events::net_error &
sanguis::client::events::net_error::operator=(
	net_error &&
)
= default;

sanguis::client::events::net_error &
sanguis::client::events::net_error::operator=(
	net_error const &
)
= default;

sanguis::client::events::net_error::~net_error()
{
}

fcppt::string const &
sanguis::client::events::net_error::message() const
{
	return
		message_;
}

boost::system::error_code const &
sanguis::client::events::net_error::code() const
{
	return
		code_;
}
