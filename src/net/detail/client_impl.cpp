#include "client_impl.hpp"
#include "is_disconnect.hpp"
#include "../exception.hpp"
#include "../log.hpp"
#undef max
// asio brings in window.h's max macro :(
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/text.hpp>
#include <boost/asio/buffer.hpp>

sanguis::net::detail::client_impl::client_impl(
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
	received_data_(),
	send_data_(
		1024 * 64
	),
	connect_signal_(),
	disconnect_signal_(),
	data_signal_()
{
}

void
sanguis::net::detail::client_impl::connect(
	hostname_type const &_host,
	port_type const _port
)
{
	FCPPT_LOG_DEBUG(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("client: resolving hostname ")
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
			fcppt::lexical_cast<std::string>(
				_port
			)
		)
	);

	resolver_.async_resolve(
		*query_,
		std::tr1::bind(
			&client_impl::resolve_handler,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2
		)
	);
}

void
sanguis::net::detail::client_impl::disconnect()
{
	socket_.close();

	this->clear();
}

void
sanguis::net::detail::client_impl::queue(
	data_type const &_data
)
{
	output_.push_back(
		_data
	);

	if(
		send_data_.capacity()
		- send_data_.size()
		<
		_data.size()
	)
	{
		// not enough space left
		// TODO: call something here and wait!
	}

	bool const sending(
		send_data_.empty()
	);

	send_data_.insert(
		_data.begin(),
		_data.end(),
		send_data_.end()
	);

	if(
		!sending
	)
		this->send_data();
}

fcppt::signal::auto_connection
sanguis::net::detail::client_impl::register_connect(
	client::connect_function const &_function
)
{
	return
		connect_signal_.connect(
			_function
		);
}

fcppt::signal::auto_connection
sanguis::net::detail::client_impl::register_disconnect(
	client::disconnect_function const &_function
)
{
	return
		disconnect_signal_.connect(
			_function
		);
}

fcppt::signal::auto_connection
sanguis::net::detail::client_impl::register_data(
	client::data_function const &_function
)
{
	return
		data_signal_.connect(
			_function
		);
}

void
sanguis::net::detail::client_impl::resolve_handler(
	boost::system::error_code const &_error
	boost::asio::ip::tcp::resolver::iterator _iterator
)
{
	if(
		_error
	)
		throw sanguis::exception(
			FCPPT_TEXT("client: error resolving address: ")+
			fcppt::from_std_string(
				_error.message()
			)
		);

	FCPPT_LOG_DEBUG(
		net::log(),
		fcppt::log::_ << FCPPT_TEXT("client: resolved domain, trying to connect")
	);
	
	boost::asio::ip::tcp::endpoint const endpoint(
		*_iterator
	);

	socket_.async_connect(
		endpoint,
		std::tr1::bind(
			&client_impl::connect_handler,
			this,
			std::tr1::placeholders::_1,
			++_iterator
		)
	);
}

void
sanguis::net::detail::client_impl::handle_error(
	fcppt::string const &_message,
	boost::system::error_code const &_error
)
{
	this->clear();

	if(
		!detail::is_disconnect(
			_error
		)
	)
		throw sanguis::exception(
			FCPPT_TEXT("error in ") +
			_message +
			FCPPT_TEXT(": ") +
			fcppt::from_std_string(
				_error.message()
			)
		);

		
	FCPPT_LOG_DEBUG(
		net::log(),
		fcppt::log::_
			<< FCPPT_TEXT("client: disconnected (")
			<< fcppt::from_std_string(
				_error.message())

			<< FCPPT_TEXT(")")
	);

	disconnect_signal_(
		fcppt::from_std_string(
			_error.message()
		)
	);
}

void
sanguis::net::detail::client_impl::read_handler(
	boost::system::error_code const &_error,
	std::size_t const _bytes
)
{
	if(
		_error
	)
	{
		this->handle_error(
			FCPPT_TEXT("client read"),
			_error
		);

		return;
	}

	FCPPT_LOG_DEBUG(
		net::log(),
		fcppt::log::_
			<< FCPPT_TEXT("client: read ")
			<< _bytes
			<< FCPPT_TEXT(" bytes.")
	);

	data_signal_(
		net::data_type(
			received_data_.begin(),
			received_data_.begin() + _bytes
		)
	);

	socket_.async_receive(
		boost::asio::buffer(
			received_data_
		),
		std::tr1::bind(
			&client_impl::read_handler,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2
		)
	);
}

void
sanguis::net::detail::client_impl::write_handler(
	boost::system::error_code const &_error,
	std::size_t const _bytes
)
{
	if(
		_error
	)
	{
		this->handle_error(
			FCPPT_TEXT("client write"),
			_error
		);

		return;
	}

	FCPPT_LOG_DEBUG(
		net::log(),
		fcppt::log::_
			<< FCPPT_TEXT("client: wrote ")
			<< _bytes 
			<< FCPPT_TEXT(" bytes")
	);

	send_data_.erase(
		bytes
	);

	// are there bytes left to send?
	if(
		!send_data_.empty()
	)
		this->send_data();
}

void
sanguis::net::detail::client_impl::connect_handler(
	boost::system::error_code const &_error
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
		)
			throw sanguis::exception(
				FCPPT_TEXT("client: exhausted endpoints: ")+
				fcppt::from_std_string(
					_error.message()
				)
			);

		FCPPT_LOG_DEBUG(
			net::log(),
			fcppt::log::_ << FCPPT_TEXT("client: resolving next endpoint")
		);
		
		boost::asio::ip::tcp::endpoint const endpoint(
			*_iterator
		);

		socket_.async_connect(
			endpoint,
			std::tr1::bind(
				&client_impl::connect_handler,
				this,
				std::tr1::placeholders::_1,
				++_iterator
			)
		);

		return;
	}

	FCPPT_LOG_DEBUG(
		net::log(),
		fcppt::log::_ << FCPPT_TEXT("client: connected")
	);

	connect_signal_();

	socket_.async_receive(
		boost::asio::buffer(
			received_data_
		),
		std::tr1::bind(
			&client_impl::read_handler,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2
		)
	);
}

void
sanguis::net::detail::client_impl::send_data()
{
	detail::circular_buffer::const_array_range const array(
		send_data_.second_array().empty()
		?
			send_data_.second_array()
		:
			send_data_.first_array()
	);

	socket_.async_send(
		boost::asio::buffer(
			array.first,
			array.second - array.first
		),
		std::tr1::bind(
			&sanguis::net::detail::client_impl::write_handler,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2
		)
	);
}

void
sanguis::net::detail::client_impl::clear()
{
	output_.clear();
}
