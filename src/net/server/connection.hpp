#ifndef SANGUIS_NET_SERVER_CONNECTION_HPP_INCLUDED
#define SANGUIS_NET_SERVER_CONNECTION_HPP_INCLUDED

#include "../circular_buffer.hpp"
#include "../static_buffer.hpp"
#include "../value_type.hpp"
#include "../id.hpp"
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

	net::static_buffer &
	received_data();

	net::circular_buffer &
	send_data();
private:
	net::id const id_;

	boost::asio::ip::tcp::socket socket_;

	net::static_buffer received_data_;

	net::circular_buffer send_data_;
};

}
}
}

#endif
