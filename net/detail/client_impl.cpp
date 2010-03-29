#include "client_impl.hpp"
#include "is_disconnect.hpp"
#include "io_service_wrapper.hpp"
#include "../exception.hpp"
#include "../log.hpp"
#undef max
// asio brings in window.h's max macro :(
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/text.hpp>
#include <boost/asio/buffer.hpp>

sanguis::net::detail::client_impl::client_impl() 
:
	io_service_(
		io_service_wrapper()
	),
	socket_(
		io_service_
	),
	resolver_(
		io_service_
	),
	handlers_(0),
	new_data_(),
	output_(),
	connected_(false),
	sending_(false),
	connect_signal_(),
	disconnect_signal_(),
	data_signal_()
{
}

void sanguis::net::detail::client_impl::connect(
	hostname_type const &s,
	port_type const port)
{
	FCPPT_LOG_DEBUG(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("client: resolving hostname ")
			<< fcppt::from_std_string(s) << FCPPT_TEXT(" on port ")
			<< port
	);
	
	boost::asio::ip::tcp::resolver::query query(
		s,
		fcppt::lexical_cast<std::string>(
			port));

	resolver_.async_resolve(
		query,
		std::tr1::bind(
			&client_impl::resolve_handler,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2
		)
	);

	handlers_++;
}

void sanguis::net::detail::client_impl::disconnect()
{
	clear();
	/* TODO: should we send this signal here? it could lead to an endless loop
	 * (in sanguis at least)
	disconnect_signal_(
		FCPPT_TEXT("Client disconnected"));
		*/
}

void sanguis::net::detail::client_impl::queue(
	data_type const &data)
{
	output_.push_back(
		data);
}

void sanguis::net::detail::client_impl::process()
{
	if (connected_ && !sending_ && output_.characters_left())
	{
		data_type const &buffer(
			output_.buffer()
		);

		sending_ = true;
		socket_.async_send(
			boost::asio::buffer(
				buffer.data(),
				buffer.size()
			),
			std::tr1::bind(
				&sanguis::net::detail::client_impl::write_handler,
				this,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			)
		);

		++handlers_;
	}

	if (!handlers_)
		return;

	boost::system::error_code e;
	io_service_.poll(
		e);
	if (e)
		throw exception(
			FCPPT_TEXT("poll error: ")+
			fcppt::from_std_string(
				e.message()));
}

fcppt::signal::auto_connection sanguis::net::detail::client_impl::register_connect(
	client::connect_function const &f)
{
	return connect_signal_.connect(
		f);
}

fcppt::signal::auto_connection sanguis::net::detail::client_impl::register_disconnect(
	client::disconnect_function const &f)
{
	return disconnect_signal_.connect(
		f);
}

fcppt::signal::auto_connection sanguis::net::detail::client_impl::register_data(
	client::data_function const &f)
{
	return data_signal_.connect(
		f);
}

void sanguis::net::detail::client_impl::resolve_handler(
	boost::system::error_code const &e,
	boost::asio::ip::tcp::resolver::iterator i)
{
	if (e)
		throw exception(
			FCPPT_TEXT("client: error resolving address: ")+
			fcppt::from_std_string(
				e.message()));

	FCPPT_LOG_DEBUG(
		log(),
		fcppt::log::_ << FCPPT_TEXT("client: resolved domain, trying to connect"));
	
	boost::asio::ip::tcp::endpoint endpoint = *i;
	socket_.async_connect(
		endpoint,
		std::tr1::bind(
			&client_impl::connect_handler,
			this,
			std::tr1::placeholders::_1,
			++i
		)
	);

	handlers_++;
}

void sanguis::net::detail::client_impl::handle_error(
	fcppt::string const &s,
	boost::system::error_code const &e)
{
	clear();

	if (!detail::is_disconnect(e))
	{
		throw exception(
			FCPPT_TEXT("error in ")+
			s+
			FCPPT_TEXT(": ")+
			fcppt::from_std_string(
				e.message()));
	}
		
	FCPPT_LOG_DEBUG(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("client: disconnected (")
			<< fcppt::from_std_string(e.message()) 
			<< FCPPT_TEXT(")"));

	disconnect_signal_(
		fcppt::from_std_string(
			e.message()
		)
	);
}

void sanguis::net::detail::client_impl::read_handler(
	boost::system::error_code const &e,
	std::size_t const bytes)
{
	--handlers_;
	
	if (e)
	{
		handle_error(
			FCPPT_TEXT("client read"),
			e);
		return;
	}

	FCPPT_LOG_DEBUG(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("client: read ")
			<< bytes
			<< FCPPT_TEXT(" bytes.")
	);

	data_signal_(
		data_type(
			new_data_.begin(),
			new_data_.begin() + bytes));

	socket_.async_receive(
		boost::asio::buffer(
			new_data_
		),
		std::tr1::bind(
			&client_impl::read_handler,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2
		)
	);

	handlers_++;
}

void sanguis::net::detail::client_impl::write_handler(
	boost::system::error_code const &e,
	std::size_t const bytes)
{
	handlers_--;

	if (e)
	{
		handle_error(
			FCPPT_TEXT("client write"),
			e);
		return;
	}

	FCPPT_LOG_DEBUG(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("client: wrote ")
			<< bytes 
			<< FCPPT_TEXT(" bytes"));

	output_.erase(
		bytes);

	// are there bytes left to send?
	if (output_.characters_left())
	{
		data_type const &buffer(
			output_.buffer()
		);

		socket_.async_send(
			boost::asio::buffer(
				buffer.data(),
				buffer.size()
			),
			std::tr1::bind(
				&client_impl::write_handler,
				this,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			)
		);

		handlers_++;
	}
	else
	{
		// if no more data is present, set sending to false
		sending_ = false;
	}
}

void sanguis::net::detail::client_impl::connect_handler(
	boost::system::error_code const &e,
	boost::asio::ip::tcp::resolver::iterator i)
{
	handlers_--;
	if (e)
	{
		// are we at the end of the endpoint list?
		if (i == boost::asio::ip::tcp::resolver::iterator())
			throw exception(
				FCPPT_TEXT("client: exhausted endpoints: ")+
				fcppt::from_std_string(
					e.message()));

		FCPPT_LOG_DEBUG(
			log(),
			fcppt::log::_ << FCPPT_TEXT("client: resolving next endpoint"));
		
		boost::asio::ip::tcp::endpoint endpoint = *i;
		socket_.async_connect(
			endpoint,
			std::tr1::bind(
				&client_impl::connect_handler,
				this,
				std::tr1::placeholders::_1,
				++i
			)
		);
		handlers_++;
		return;
	}

	FCPPT_LOG_DEBUG(
		log(),
		fcppt::log::_ << FCPPT_TEXT("client: connected"));

	// first connect to true, _then_ call signal
	connected_ = true;
	connect_signal_();
	socket_.async_receive(
		boost::asio::buffer(
			new_data_),
		std::tr1::bind(
			&client_impl::read_handler,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2
		)
	);

	handlers_++;
}

void sanguis::net::detail::client_impl::clear()
{
	connected_ = sending_ = false;
	output_.clear();
}
