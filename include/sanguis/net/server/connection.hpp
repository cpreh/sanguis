#ifndef SANGUIS_NET_SERVER_CONNECTION_HPP_INCLUDED
#define SANGUIS_NET_SERVER_CONNECTION_HPP_INCLUDED

#include <sanguis/net/circular_buffer.hpp>
#include <sanguis/net/id.hpp>
#include <sanguis/net/receive_buffer.hpp>
#include <sanguis/net/value_type.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace net
{
namespace server
{

class connection
{
	FCPPT_NONCOPYABLE(
		connection
	);
public:
	connection(
		net::id,
		boost::asio::io_service &
	);

	~connection();

	net::id const
	id() const;

	boost::asio::ip::tcp::socket &
	socket();

	net::circular_buffer &
	send_data();

	net::receive_buffer &
	received_data();

	bool &
	sending();
private:
	net::id const id_;

	boost::asio::ip::tcp::socket socket_;

	net::circular_buffer send_data_;

	net::receive_buffer received_data_;

	bool sending_;
};

}
}
}

#endif
