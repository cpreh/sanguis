#include <sanguis/net/is_disconnect.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/error.hpp>
#include <boost/system/error_code.hpp>
#include <fcppt/config/external_end.hpp>


bool
sanguis::net::is_disconnect(
	boost::system::error_code const &_error
)
{
	switch(
		_error.value()
	)
	{
	case boost::asio::error::connection_aborted:
	case boost::asio::error::connection_reset:
	case boost::asio::error::network_reset:
	case boost::asio::error::timed_out:
	case boost::asio::error::eof:
		return true;
	default:
		return false;
	}
}
