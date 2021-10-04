#ifndef SANGUIS_CLIENT_SERVER_HPP_INCLUDED
#define SANGUIS_CLIENT_SERVER_HPP_INCLUDED

#include <sanguis/client/server_fwd.hpp>
#include <sanguis/server/object.hpp>
#include <alda/net/port.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <mutex>
#include <thread>
#include <fcppt/config/external_end.hpp>


namespace sanguis::client
{

class server
{
	FCPPT_NONMOVABLE(
		server
	);
public:
	server(
		fcppt::log::context_reference,
		alda::net::port
	);

	void
	quit();

	awl::main::exit_code
	run();

	[[nodiscard]]
	bool
	running() const;

	~server();
private:
	void
	mainloop();

	void
	reset_running();

	fcppt::log::object log_;

	bool running_;

	sanguis::server::object impl_;

	mutable std::mutex mutex_;

	std::thread server_thread_;
};

}

#endif
