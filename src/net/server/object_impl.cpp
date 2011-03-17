#include "object_impl.hpp"
#include "connection.hpp"
#include "../append_to_circular_buffer.hpp"
#include "../circular_buffer_part.hpp"
#include "../erase_circular_buffer_front.hpp"
#include "../exception.hpp"
#include "../is_disconnect.hpp"
#include "../log.hpp"
#undef max
// asio brings in window.h's max macro :(
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio.hpp>

sanguis::net::server::object_impl::object_impl(
	boost::asio::io_service &_io_service
)
:
	io_service_(
		_io_service
	),
	acceptor_(
		io_service_
	),
	id_counter_(
		static_cast<
			net::id::value_type
		>(
			0u
		)
	),
	new_connection_(),
	connections_(),
	connect_signal_(),
	disconnect_signal_(),
	data_signal_()
{
}

sanguis::net::server::object_impl::~object_impl()
{
}

void 
sanguis::net::server::object_impl::listen(
	net::port const _port
)
{
	FCPPT_LOG_DEBUG(
		net::log(),
		fcppt::log::_
			<< FCPPT_TEXT("server: listening on port ")
			<< _port
	);

	boost::asio::ip::tcp::endpoint const endpoint(
		boost::asio::ip::tcp::v4(),
		_port
	);

	acceptor_.open(
		endpoint.protocol()
	);

	acceptor_.set_option(
		boost::asio::ip::tcp::acceptor::reuse_address(
			true
		)
	);

	acceptor_.bind(
		endpoint
	);

	acceptor_.listen();

	this->accept();
}

void 
sanguis::net::server::object_impl::queue(
	net::id const _id,
	net::data_buffer const &_data
)
{
	connection_container::iterator const it(
		connections_.find(
			_id
		)
	);

	if(
		it == connections_.end()
	)
		throw net::exception(
			FCPPT_TEXT("Invalid id in server")
			+
			fcppt::lexical_cast<
				fcppt::string
			>(
				_id
			)
		);


	server::connection &con(
		*it->second
	);

	bool const sending(
		!con.send_data().empty()
	);

	if(
		!net::append_to_circular_buffer(
			con.send_data(),
			_data
		)
	)
	{
		// TODO: wait or drop this client?
	}

	if(
		!sending
	)
		this->send_data(
			con
		);
}

fcppt::signal::auto_connection
sanguis::net::server::object_impl::register_connect(
	server::connect_callback const &_callback
)
{
	return
		connect_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sanguis::net::server::object_impl::register_disconnect(
	server::disconnect_callback const &_callback
)
{
	return
		disconnect_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection 
sanguis::net::server::object_impl::register_data(
	server::data_callback const &_callback
)
{
	return
		data_signal_.connect(
			_callback
		);
}

void 
sanguis::net::server::object_impl::stop()
{
	io_service_.stop();
}

void 
sanguis::net::server::object_impl::accept()
{
	new_connection_ =
		fcppt::make_unique_ptr<
			server::connection
		>(
			net::id(
				id_counter_++
			),
			fcppt::ref(
				io_service_
			)
		);

	acceptor_.async_accept(
		new_connection_->socket(),
		std::tr1::bind(
			&object_impl::accept_handler,
			this,
			std::tr1::placeholders::_1
		)
	);
}

void 
sanguis::net::server::object_impl::read_handler(
	boost::system::error_code const &_error,
	std::size_t const _bytes,
	server::connection &_con
)
{
	if(
		_error
	)
	{
		this->handle_error(
			FCPPT_TEXT("server read"),
			_error,
			_con
		);

		return;
	}

	FCPPT_LOG_DEBUG(
		net::log(),
		fcppt::log::_
			<< FCPPT_TEXT("server: reading ")
			<< _bytes 
			<< FCPPT_TEXT(" bytes.")
	);
	
	// TODO: optimize!
	_con.received_data().insert(
		_con.received_data().end(),
		_con.new_data().begin(),
		_con.new_data().begin() + _bytes
	);

	data_signal_(
		_con.id(),
		fcppt::ref(
			_con.received_data()
		)
	);

	// receive some more
	_con.socket().async_receive(
		boost::asio::buffer(
			_con.new_data()
		),
		std::tr1::bind(
			&object_impl::read_handler,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2,
			fcppt::ref(
				_con
			)
		)
	);
}

void 
sanguis::net::server::object_impl::write_handler(
	boost::system::error_code const &_error,
	std::size_t const _bytes,
	server::connection &_con
)
{
	if(
		_error
	)
	{
		this->handle_error(
			FCPPT_TEXT("server write"),
			_error,
			_con
		);

		return;
	}

	FCPPT_LOG_DEBUG(
		net::log(),
		fcppt::log::_
			<< FCPPT_TEXT("server: wrote ")
			<< _bytes 
			<< FCPPT_TEXT(" bytes.")
	);

	net::circular_buffer &send_data(
		_con.send_data()
	);

	net::erase_circular_buffer_front(
		send_data,
		_bytes
	);

	if(
		!send_data.empty()
	)
		this->send_data(
			_con
		);
}

void 
sanguis::net::server::object_impl::accept_handler(
	boost::system::error_code const &_error
)
{
	if(
		_error
	)
	{
		FCPPT_LOG_DEBUG(
			net::log(),
			fcppt::log::_
				<< FCPPT_TEXT("server: error while accepting")
		);

		this->accept();

		return;
	}

	FCPPT_LOG_DEBUG(
		net::log(),
		fcppt::log::_
			<< FCPPT_TEXT("server: accepting a connection, id is ")
			<< new_connection_->id()
	);

	FCPPT_ASSERT(
		new_connection_
	);

	server::connection &current_con(
		*new_connection_
	);

	if(
		!fcppt::container::ptr::insert_unique_ptr_map(
			connections_,
			current_con.id(),
			move(
				new_connection_
			)
		).second
	)
		throw net::exception(
			FCPPT_TEXT("Double insert in net::server!")
		);
	
	// send signal to handlers
	connect_signal_(
		current_con.id()
	);

	current_con.socket().async_receive(
		boost::asio::buffer(
			current_con.new_data()
		),
		std::tr1::bind(
			&object_impl::read_handler,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2,
			std::tr1::ref(
				current_con
			)
		)
	);

	this->accept();
}

void 
sanguis::net::server::object_impl::handle_error(
	fcppt::string const &_message,
	boost::system::error_code const &_error,
	server::connection const &_con
)
{
	fcppt::string const error_msg(
		fcppt::from_std_string(
			_error.message()
		)
	);

	// do we have an error or a disconnect...
	if(
		net::is_disconnect(
			_error
		)
	)
		throw net::exception(
			_message
			+
			FCPPT_TEXT(" error: ")
			+
			error_msg
		);

	FCPPT_LOG_DEBUG(
		net::log(),
		fcppt::log::_
			<< FCPPT_TEXT("server: disconnected ")
			<< _con.id() 
			<< FCPPT_TEXT(" (")
			<< error_msg
			<< FCPPT_TEXT(")")
	);

	// ...else remove connection
	disconnect_signal_(
		_con.id(),
		error_msg
	);

	if(
		!connections_.erase(
			_con.id()
		)
	)
		throw net::exception(
			FCPPT_TEXT("Invalid erase in net::server!")
		);
}

void
sanguis::net::server::object_impl::send_data(
	server::connection &_con
)
{
	net::circular_buffer::const_array_range const out_data(
		net::circular_buffer_part(
			_con.send_data()
		)
	);

	if(
		out_data.second == 0u
	)
		return;

	_con.socket().async_send(
		boost::asio::buffer(
			out_data.first,
			out_data.second
		),
		std::tr1::bind(
			&object_impl::write_handler,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2,
			fcppt::ref(
				_con
			)
		)
	);
}
