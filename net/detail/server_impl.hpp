#ifndef SANGUIS_NET_DETAIL_SERVER_IMPL_HPP_INCLUDED
#define SANGUIS_NET_DETAIL_SERVER_IMPL_HPP_INCLUDED

#include "server_impl_fwd.hpp"
#include "../server.hpp"
#include "../id_type.hpp"
#include "../port_type.hpp"
#include "../data_type.hpp"
#include "connection_fwd.hpp"
#include <boost/system/error_code.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/auto_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <cstddef>

namespace sanguis
{
namespace net
{
namespace detail
{

class server_impl
{
	FCPPT_NONCOPYABLE(server_impl)
public:
	explicit
	server_impl(
		server::time_resolution const &);

	void
	listen(
		port_type);

	void
	process();

	void
	queue(
		id_type,
		data_type const &);

	void
	queue(
		data_type const &);

	fcppt::signal::auto_connection
	register_connect(
		server::connect_function const &);

	fcppt::signal::auto_connection
	register_disconnect(
		server::disconnect_function const &);
	
	fcppt::signal::auto_connection
	register_data(
		server::data_function const &);

	fcppt::signal::auto_connection
	register_timer(
		server::timer_function const &);

	void
	run();

	void
	stop();
private:
	typedef boost::ptr_vector<connection> connection_container;

	boost::asio::io_service io_service_;
	boost::asio::ip::tcp::acceptor acceptor_;

	id_type id_counter_;
	fcppt::auto_ptr<connection> new_connection_;
	connection_container connections_;

	server::time_resolution const timer_duration_;

	// NOTE: The deadline_timer is gone after it first triggers
	// so we have to create a new one every time
	fcppt::auto_ptr<boost::asio::deadline_timer> timer_;

	fcppt::signal::object<server::connect_fun> connect_signal_;
	fcppt::signal::object<server::disconnect_fun> disconnect_signal_;
	fcppt::signal::object<server::data_fun> data_signal_;
	fcppt::signal::object<server::timer_fun> timer_signal_;

	void
	accept();

	void
	read_handler(
		boost::system::error_code const &,
		std::size_t,
		connection &
	);

	void
	write_handler(
		boost::system::error_code const &,
		std::size_t,
		connection &
	);

	void
	accept_handler(
		boost::system::error_code const &
	);

	void
	handle_error(
		fcppt::string const &,
		boost::system::error_code const &,
		connection const &
	);

	void
	handle_timeout(
		boost::system::error_code const &);
};

}
}
}

#endif // SANGUIS_NET_DETAIL_SERVER_IMPL_HPP_INCLUDED
