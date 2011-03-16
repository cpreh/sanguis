#ifndef SANGUIS_NET_SERVER_CONNECTION_HPP_INCLUDED
#define SANGUIS_NET_SERVER_CONNECTION_HPP_INCLUDED

#include "../circular_buffer.hpp"
#include "../data_buffer.hpp"
#include "../id.hpp"
#include "../static_buffer.hpp"
#include "../value_type.hpp"
#include <fcppt/container/raw_vector_decl.hpp>
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
	new_data();

	net::circular_buffer &
	send_data();

	net::data_buffer &
	received_data();
private:
	net::id const id_;

	boost::asio::ip::tcp::socket socket_;

	net::static_buffer new_data_;

	net::circular_buffer send_data_;

	net::data_buffer received_data_;
};

}
}
}

#endif
