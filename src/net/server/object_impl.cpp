#include "object_impl.hpp"
#include "connection.hpp"
#include "../append_to_circular_buffer.hpp"
#include "../circular_buffer_send_part.hpp"
#include "../erase_circular_buffer_front.hpp"
#include "../exception.hpp"
#include "../is_disconnect.hpp"
#include "../log.hpp"
#include "../receive_buffer.hpp"
#include "../receive_buffer_for_asio.hpp"
#include "../receive_buffer_part.hpp"
#undef max
// asio brings in window.h's max macro :(
#include <fcppt/chrono/duration_cast.hpp>
#include <fcppt/chrono/duration_impl.hpp>
#include <fcppt/chrono/milliseconds.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio.hpp>

sanguis::net::server::object_impl::object_impl(
	boost::asio::io_service &_io_service,
	sge::time::duration const &_duration
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
	data_signal_(),
	timer_signal_(),
	timer_duration_(
		fcppt::chrono::duration_cast<
			fcppt::chrono::milliseconds
		>(
			_duration
		).count()
	),
	deadline_timer_(
		io_service_
	)
{
	this->reset_timer();
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
		object_impl::log(),
		fcppt::log::_
			<< FCPPT_TEXT("listening on port ")
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

sanguis::net::circular_buffer &
sanguis::net::server::object_impl::send_buffer(
	net::id const _id
)
{
	return
		this->connection(
			_id
		).send_data();
}

void 
sanguis::net::server::object_impl::queue_send(
	net::id const _id
)
{
	server::connection &con(
		this->connection(
			_id
		)
	);

	if(
		!con.sending()
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

fcppt::signal::auto_connection
sanguis::net::server::object_impl::register_timer(
	server::timer_callback const &_callback
)
{
	return
		timer_signal_.connect(
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
		object_impl::log(),
		fcppt::log::_
			<< FCPPT_TEXT("reading ")
			<< _bytes 
			<< FCPPT_TEXT(" bytes.")
	);

	_con.received_data().bytes_received(
		_bytes
	);
	
	data_signal_(
		_con.id(),
		fcppt::ref(
			_con.received_data()
		)
	);

	this->receive_data(
		_con
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
			FCPPT_TEXT("write"),
			_error,
			_con
		);

		return;
	}

	FCPPT_LOG_DEBUG(
		object_impl::log(),
		fcppt::log::_
			<< FCPPT_TEXT("wrote ")
			<< _bytes 
			<< FCPPT_TEXT(" bytes.")
	);

	net::circular_buffer &sent_data(
		_con.send_data()
	);

	net::erase_circular_buffer_front(
		sent_data,
		_bytes
	);

	if(
		!sent_data.empty()
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
			object_impl::log(),
			fcppt::log::_
				<< FCPPT_TEXT("error while accepting")
		);

		this->accept();

		return;
	}

	FCPPT_LOG_DEBUG(
		object_impl::log(),
		fcppt::log::_
			<< FCPPT_TEXT("accepting a connection, id is ")
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

	this->receive_data(
		current_con
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
		object_impl::log(),
		fcppt::log::_
			<< FCPPT_TEXT("disconnected ")
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
sanguis::net::server::object_impl::timer_handler()
{
	timer_signal_();
}

void
sanguis::net::server::object_impl::send_data(
	server::connection &_con
)
{
	net::circular_buffer::const_array_range const out_data(
		net::circular_buffer_send_part(
			_con.send_data()
		)
	);

	_con.sending() = (out_data.second != 0u);

	if(
		!_con.sending()
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

void
sanguis::net::server::object_impl::receive_data(
	server::connection &_con
)
{
	FCPPT_ASSERT(
		!_con.received_data().next_receive_part().empty()
	);

	// receive some more
	_con.socket().async_receive(
		net::receive_buffer_for_asio(
			_con.received_data()
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
sanguis::net::server::object_impl::reset_timer()
{
	deadline_timer_.expires_from_now(
		timer_duration_
	);

	deadline_timer_.async_wait(
		std::tr1::bind(
			&object_impl::timer_handler,
			this
		)
	);
}

sanguis::net::server::connection &
sanguis::net::server::object_impl::connection(
	net::id const _id
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
	
	return *it->second;
}

fcppt::log::object &
sanguis::net::server::object_impl::log()
{
	static fcppt::log::object my_logger(
		fcppt::log::parameters::inherited(
			net::log(),
			FCPPT_TEXT("server")
		)
	);

	return my_logger;
}
