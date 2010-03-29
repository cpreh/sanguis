#include "connection.hpp"

sanguis::net::detail::connection::connection(
	id_type const _id,
	boost::asio::io_service &_io_service) 
	: id_(_id),
	  socket_(_io_service),
		new_data_(),
		output_(),
		sending_(false) 
{}
