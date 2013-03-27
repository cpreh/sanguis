#ifndef SANGUIS_SERVER_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_OBJECT_HPP_INCLUDED

#include <sanguis/server/machine.hpp>
#include <sanguis/server/object_fwd.hpp>
#include <sanguis/main_object.hpp>
#include <sanguis/io_service.hpp>
#include <alda/net/port.hpp>
#include <fcppt/scoped_state_machine.hpp>
#include <fcppt/noncopyable.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/config/external_begin.hpp>
#include <mutex>
#include <thread>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{

class object
:
	public sanguis::main_object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit
	object(
		alda::net::port
	);

	void
	quit();

	awl::main::exit_code const
	run();

	bool
	running() const;

	~object();
private:
	void
	mainloop();

	void
	timer_callback();

	void
	reset_running();

	bool running_;

	sanguis::io_service io_service_;

	sanguis::server::machine machine_;

	typedef fcppt::scoped_state_machine<
		sanguis::server::machine
	> scoped_machine;

	scoped_machine scoped_machine_;

	mutable std::mutex mutex_;

	std::thread server_thread_;
};

}
}

#endif
