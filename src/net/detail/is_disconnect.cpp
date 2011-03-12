#include "is_disconnect.hpp"
#include <boost/asio/error.hpp>

bool sanguis::net::detail::is_disconnect(boost::system::error_code const &e)
{
	switch(e.value()) 
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
