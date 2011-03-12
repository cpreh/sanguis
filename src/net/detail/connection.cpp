#include "connection.hpp"

sanguis::net::detail::connection::connection(
	net::id const _id,
	boost::asio::io_service &_io_service
)
:
	id_(_id),
	socket_(
		_io_service
	),
	received_data_(),
	send_data_()
{
}

sanguis::net::detail::connection::~connection()
{
}

sanguis::net::id const
sanguis::net::detail::connection::id() const
{
	return id_;
}

boost::asio::ip::tcp::socket &
sanguis::net::detail::connection::socket()
{
	return socket_;
}

sanguis::net::detail::static_buffer &
sanguis::net::detail::connection::received_data()
{
	return received_data_;
}

sanguis::net::detail::circular_buffer &
sanguis::net::detail::connection::send_data()
{
	return send_data_;
}
