#ifndef SANGUIS_NET_SERVER_CONNECTION_HPP_INCLUDED
#define SANGUIS_NET_SERVER_CONNECTION_HPP_INCLUDED

#include "../circular_buffer.hpp"
#include "../id.hpp"
#include "../receive_buffer.hpp"
#include "../value_type.hpp"
#include <fcppt/noncopyable.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

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
