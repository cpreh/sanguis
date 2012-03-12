#ifndef SANGUIS_SERVER_MACHINE_HPP_INCLUDED
#define SANGUIS_SERVER_MACHINE_HPP_INCLUDED

#include <sanguis/server/machine_fwd.hpp>
#include <sanguis/server/states/running_fwd.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/load/context_base_fwd.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <sanguis/messages/base_fwd.hpp>
#include <sanguis/net/server/object.hpp>
#include <sanguis/net/data_buffer.hpp>
#include <sanguis/net/id.hpp>
#include <sanguis/net/port.hpp>
#include <sanguis/net/receive_buffer_fwd.hpp>
#include <sanguis/timer.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <fcppt/container/raw_vector_decl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <awl/mainloop/io_service_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/state_machine.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace server
{

struct machine
:
	public boost::statechart::state_machine<
		machine,
		states::running
	>
{
	FCPPT_NONCOPYABLE(
		machine
	);
public:
	machine(
		load::context_base const &,
		sge::charconv::system &,
		net::port,
		awl::mainloop::io_service &
	);

	~machine();

	void
	listen();

	void
	stop();

	void
	send_to_all(
		messages::base const &
	);

	void
	send_unicast(
		server::player_id,
		messages::base const &
	);

	load::context_base const &
	resources() const;

	sge::charconv::system &
	charconv_system() const;
private:
	void
	process_message(
		net::id,
		messages::auto_ptr
	);

	void
	connect_callback(
		net::id
	);

	void
	disconnect_callback(
		net::id,
		fcppt::string const &
	);

	void
	data_callback(
		net::id,
		net::receive_buffer &
	);

	void
	timer_callback();

	load::context_base const &resources_;

	sge::charconv::system &charconv_system_;

	net::port const port_;

	net::server::object net_;

	sanguis::timer frame_timer_;

	net::data_buffer temp_buffer_;

	fcppt::signal::scoped_connection const
		s_conn_,
		s_disconn_,
		s_data_,
		s_timer_;
};

}
}

#endif
