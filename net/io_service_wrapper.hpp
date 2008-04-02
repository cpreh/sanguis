#ifndef IO_SERVICE_WRAPPER_HPP_INCLUDED
#define IO_SERVICE_WRAPPER_HPP_INCLUDED

#include <boost/asio/io_service.hpp>

namespace net
{

boost::asio::io_service &io_service_wrapper();

}

#endif
