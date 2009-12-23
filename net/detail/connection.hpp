#ifndef SANGUIS_NET_DETAIL_CONNECTION_HPP_INCLUDED
#define SANGUIS_NET_DETAIL_CONNECTION_HPP_INCLUDED

#include "output_buffer.hpp"
#include "static_buffer.hpp"
#include "../value_type.hpp"
#include "../id_type.hpp"
#include <fcppt/noncopyable.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace sanguis
{
namespace net
{
namespace detail
{

class connection {
	FCPPT_NONCOPYABLE(connection)
public:
	connection(
		id_type,
		boost::asio::io_service &);

	id_type const id_;
	boost::asio::ip::tcp::socket socket_;
	static_buffer new_data_;
	output_buffer output_;
	bool connected_,sending_;

};

}
}
}

#endif
