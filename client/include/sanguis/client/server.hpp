#ifndef SANGUIS_CLIENT_SERVER_HPP_INCLUDED
#define SANGUIS_CLIENT_SERVER_HPP_INCLUDED

#include <sanguis/client/server_fwd.hpp>
#include <sanguis/server/object.hpp>
#include <alda/net/port.hpp>
#include <fcppt/noncopyable.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/config/external_begin.hpp>
#include <mutex>
#include <thread>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{

class server
{
	FCPPT_NONCOPYABLE(
		server
	);
public:
	explicit
	server(
		alda::net::port
	);

	void
	quit();

	awl::main::exit_code const
	run();

	bool
	running() const;

	~server();
private:
	void
	mainloop();

	void
	reset_running();

	bool running_;

	sanguis::server::object impl_;

	mutable std::mutex mutex_;

	std::thread server_thread_;
};

}
}

#endif
