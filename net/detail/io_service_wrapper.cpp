#include "io_service_wrapper.hpp"

boost::asio::io_service &
sanguis::net::detail::io_service_wrapper()
{
	static boost::asio::io_service io;
	return io;
}
