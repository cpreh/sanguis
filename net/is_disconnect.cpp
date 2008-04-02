#include "is_disconnect.hpp"

bool net::is_disconnect(const boost::system::error_code &e)
{
	switch(e.value()) {
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
