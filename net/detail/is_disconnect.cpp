#include "is_disconnect.hpp"

bool sanguis::net::detail::is_disconnect(boost::system::error_code const &e)
{
	switch(e.value()) 
	{
	case boost::system::posix_error::connection_aborted:
	case boost::system::posix_error::connection_reset:
	case boost::system::posix_error::network_reset:
	case boost::system::posix_error::timed_out:
//	case boost::system::posix_error::eof:
		return true;
	default:
		return false;
	}
}
