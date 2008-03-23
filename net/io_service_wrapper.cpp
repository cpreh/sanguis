#include "io_service_wrapper.hpp"

asio::io_service &io_service_wrapper()
{
	static asio::io_service io;
	return io;
}
