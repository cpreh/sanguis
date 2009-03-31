#ifndef SANGUIS_NET_DETAIL_IO_SERVICE_WRAPPER_HPP_INCLUDED
#define SANGUIS_NET_DETAIL_IO_SERVICE_WRAPPER_HPP_INCLUDED

#include <boost/asio/io_service.hpp>

namespace sanguis
{
namespace net
{
namespace detail
{
boost::asio::io_service &io_service_wrapper();
}
}
}

#endif
