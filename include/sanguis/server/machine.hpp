#ifndef SANGUIS_SERVER_MACHINE_HPP_INCLUDED
#define SANGUIS_SERVER_MACHINE_HPP_INCLUDED

#include <sanguis/io_service_fwd.hpp>
#include <sanguis/timer.hpp>
#include <sanguis/load/server_context.hpp>
#include <sanguis/messages/base_fwd.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/net/data_buffer.hpp>
#include <sanguis/server/machine_fwd.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/timer.hpp>
#include <sanguis/server/states/running_fwd.hpp>
#include <alda/net/id.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/circular_receive/object_fwd.hpp>
#include <alda/net/server/object.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
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
		sanguis::server::machine,
		sanguis::server::states::running
	>
{
	FCPPT_NONCOPYABLE(
		machine
	);
public:
	machine(
		alda::net::port,
		sanguis::io_service &
	);

	~machine();

	void
	listen();

	void
	send_to_all(
		sanguis::messages::base const &
	);

	void
	send_unicast(
		sanguis::server::player_id,
		sanguis::messages::base const &
	);

	sanguis::load::server_context const &
	resources() const;
private:
	void
	process_message(
		alda::net::id,
		sanguis::messages::unique_ptr &&
	);

	void
	disconnect_callback(
		alda::net::id,
		fcppt::string const &
	);

	void
	data_callback(
		alda::net::id,
		alda::net::buffer::circular_receive::object &
	);

	void
	timer_callback();

	sanguis::load::server_context resources_;

	alda::net::port const port_;

	sanguis::io_service &io_service_;

	alda::net::server::object net_;

	sanguis::timer frame_timer_;

	sanguis::net::data_buffer temp_buffer_;

	fcppt::signal::scoped_connection const
		disconnect_connection_,
		data_connection_;

	sanguis::server::timer timer_;
};

}
}

#endif
