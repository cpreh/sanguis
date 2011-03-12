#ifndef SANGUIS_NET_DETAIL_CONNECTION_HPP_INCLUDED
#define SANGUIS_NET_DETAIL_CONNECTION_HPP_INCLUDED

#include "circular_buffer.hpp"
#include "static_buffer.hpp"
#include "../value_type.hpp"
#include "../id.hpp"
#include <fcppt/noncopyable.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace sanguis
{
namespace net
{
namespace detail
{

class connection
{
	FCPPT_NONCOPYABLE(
		connection
	);
public:
	connection(
		net::id_type,
		boost::asio::io_service &
	);

	~connection();

	net::id const
	id() const;

	boost::asio::ip::tcp::socket &
	socket();

	detail::static_buffer &
	received_data();

	detail::circular_buffer &
	send_data();
private:
	net::id const id_;

	boost::asio::ip::tcp::socket socket_;

	detail::static_buffer received_data_;

	detail::circuluar_buffer send_data_;
};

}
}
}

#endif
