#include "connection.hpp"
#include "../send_buffer_size.hpp"
#include <fcppt/container/raw_vector_impl.hpp>

sanguis::net::server::connection::connection(
	net::id const _id,
	boost::asio::io_service &_io_service
)
:
	id_(_id),
	socket_(
		_io_service
	),
	new_data_(),
	send_data_(
		net::send_buffer_size()
	),
	received_data_()
{
}

sanguis::net::server::connection::~connection()
{
}

sanguis::net::id const
sanguis::net::server::connection::id() const
{
	return id_;
}

boost::asio::ip::tcp::socket &
sanguis::net::server::connection::socket()
{
	return socket_;
}

sanguis::net::static_buffer &
sanguis::net::server::connection::new_data()
{
	return new_data_;
}

sanguis::net::data_buffer &
sanguis::net::server::connection::received_data()
{
	return received_data_;
}

sanguis::net::circular_buffer &
sanguis::net::server::connection::send_data()
{
	return send_data_;
}
