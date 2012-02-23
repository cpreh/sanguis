#include <sanguis/net/client/object_impl.hpp>
#include <sanguis/net/append_to_circular_buffer.hpp>
#include <sanguis/net/circular_buffer_send_part.hpp>
#include <sanguis/net/erase_circular_buffer_front.hpp>
#include <sanguis/net/exception.hpp>
#include <sanguis/net/log_location.hpp>
#include <sanguis/net/receive_buffer_for_asio.hpp>
#include <sanguis/net/receive_buffer_part.hpp>
#include <sanguis/net/receive_buffer_size.hpp>
#include <sanguis/net/send_buffer_size.hpp>
#include <sanguis/log_parameters.hpp>
#undef max
// asio brings in window.h's max macro :(
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/verbose.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/insert_to_std_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/buffer.hpp>
#include <fcppt/config/external_end.hpp>

namespace
{

fcppt::log::object logger(
	sanguis::log_parameters(
		sanguis::net::log_location()
		/
		FCPPT_TEXT("client")
	)
);

}

sanguis::net::client::object_impl::object_impl(
	boost::asio::io_service &_io_service
)
:
	io_service_(
		_io_service
	),
	socket_(
		io_service_
	),
	resolver_(
		io_service_
	),
	query_(),
	receive_buffer_(
		net::receive_buffer_size()
	),
	send_buffer_(
		net::send_buffer_size()
	),
	connect_signal_(),
	error_signal_(),
	data_signal_(),
	sending_(false)
{
}

sanguis::net::client::object_impl::~object_impl()
{
}

void
sanguis::net::client::object_impl::connect(
	net::hostname const &_host,
	net::port const _port
)
{
	FCPPT_LOG_DEBUG(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("resolving hostname ")
			<< fcppt::from_std_string(
				_host
			)
			<< FCPPT_TEXT(" on port ")
			<< _port
	);

	query_.take(
		fcppt::make_unique_ptr<
			boost::asio::ip::tcp::resolver::query
		>(
			_host,
			fcppt::insert_to_std_string(
				_port
			)
		)
	);

	resolver_.async_resolve(
		*query_,
		std::tr1::bind(
			&object_impl::resolve_handler,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2
		)
	);
}

void
sanguis::net::client::object_impl::disconnect()
{
	this->clear();
}

sanguis::net::circular_buffer &
sanguis::net::client::object_impl::send_buffer()
{
	return send_buffer_;
}

void
sanguis::net::client::object_impl::queue_send()
{
	if(
		!sending_
	)
		this->send_data();
}

fcppt::signal::auto_connection
sanguis::net::client::object_impl::register_connect(
	client::connect_callback const &_function
)
{
	return
		connect_signal_.connect(
			_function
		);
}

fcppt::signal::auto_connection
sanguis::net::client::object_impl::register_error(
	client::error_callback const &_function
)
{
	return
		error_signal_.connect(
			_function
		);
}

fcppt::signal::auto_connection
sanguis::net::client::object_impl::register_data(
	client::data_callback const &_function
)
{
	return
		data_signal_.connect(
			_function
		);
}

void
sanguis::net::client::object_impl::resolve_handler(
	boost::system::error_code const &_error,
	boost::asio::ip::tcp::resolver::iterator _iterator
)
{
	if(
		_error
	)
	{
		this->handle_error(
			FCPPT_TEXT("resolving address: ")
			+
			fcppt::from_std_string(
				_error.message()
			),
			_error
		);

		return;
	}

	FCPPT_LOG_DEBUG(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("resolved domain, trying to connect")
	);

	boost::asio::ip::tcp::endpoint const endpoint(
		*_iterator
	);

	socket_.async_connect(
		endpoint,
		std::tr1::bind(
			&object_impl::connect_handler,
			this,
			std::tr1::placeholders::_1,
			++_iterator
		)
	);
}

void
sanguis::net::client::object_impl::handle_error(
	fcppt::string const &_message,
	boost::system::error_code const &_error
)
{
	this->clear();

	FCPPT_LOG_ERROR(
		::logger,
		fcppt::log::_
			<< _message
			<< FCPPT_TEXT(" (")
			<< fcppt::from_std_string(
				_error.message()
			)
			<< FCPPT_TEXT(')')
	);

	error_signal_(
		_message,
		_error
	);
}

void
sanguis::net::client::object_impl::read_handler(
	boost::system::error_code const &_error,
	std::size_t const _bytes
)
{
	if(
		_error
	)
	{
		this->handle_error(
			FCPPT_TEXT("read"),
			_error
		);

		return;
	}

	receive_buffer_.bytes_received(
		_bytes
	);

	FCPPT_LOG_VERBOSE(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("read ")
			<< _bytes
			<< FCPPT_TEXT(" bytes.")
	);

	data_signal_(
		fcppt::ref(
			receive_buffer_
		)
	);

	this->receive_data();
}

void
sanguis::net::client::object_impl::write_handler(
	boost::system::error_code const &_error,
	std::size_t const _bytes
)
{
	if(
		_error
	)
	{
		this->handle_error(
			FCPPT_TEXT("write "),
			_error
		);

		return;
	}

	FCPPT_LOG_VERBOSE(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("wrote ")
			<< _bytes
			<< FCPPT_TEXT(" bytes")
	);

	net::erase_circular_buffer_front(
		send_buffer_,
		_bytes
	);

	if(
		!send_buffer_.empty()
	)
		this->send_data();
	else
		sending_ = false;
}

void
sanguis::net::client::object_impl::connect_handler(
	boost::system::error_code const &_error,
	boost::asio::ip::tcp::resolver::iterator _iterator
)
{
	if(
		_error
	)
	{
		// are we at the end of the endpoint list?
		if(
			_iterator == boost::asio::ip::tcp::resolver::iterator()
			|| _error == boost::asio::error::operation_aborted
		)
		{
			this->handle_error(
				FCPPT_TEXT("exhausted endpoints or connection aborted: ")+
				fcppt::from_std_string(
					_error.message()
				),
				_error
			);

			return;
		}

		FCPPT_LOG_DEBUG(
			::logger,
			fcppt::log::_
				<< FCPPT_TEXT("resolving next endpoint")
		);

		boost::asio::ip::tcp::endpoint const endpoint(
			*_iterator
		);

		socket_.async_connect(
			endpoint,
			std::tr1::bind(
				&object_impl::connect_handler,
				this,
				std::tr1::placeholders::_1,
				++_iterator
			)
		);

		return;
	}

	FCPPT_LOG_DEBUG(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("connected")
	);

	connect_signal_();

	this->receive_data();
}

void
sanguis::net::client::object_impl::send_data()
{
	net::circular_buffer::const_array_range const array(
		net::circular_buffer_send_part(
			send_buffer_
		)
	);

	sending_ = (array.second != 0u);

	if(
		!sending_
	)
		return;

	socket_.async_send(
		boost::asio::buffer(
			array.first,
			array.second
		),
		std::tr1::bind(
			&sanguis::net::client::object_impl::write_handler,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2
		)
	);
}

void
sanguis::net::client::object_impl::receive_data()
{
	FCPPT_ASSERT_PRE(
		!receive_buffer_.next_receive_part().empty()
	);

	socket_.async_receive(
		net::receive_buffer_for_asio(
			receive_buffer_
		),
		std::tr1::bind(
			&object_impl::read_handler,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2
		)
	);
}

void
sanguis::net::client::object_impl::clear()
{
	resolver_.cancel();

	query_.reset();

	socket_.close();

	send_buffer_.clear();

	receive_buffer_.clear();

	sending_ = false;
}
