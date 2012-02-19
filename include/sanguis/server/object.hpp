#ifndef SANGUIS_SERVER_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_OBJECT_HPP_INCLUDED

#include <sanguis/server/machine.hpp>
#include <sanguis/server/object_fwd.hpp>
#include <sanguis/load/context_base_fwd.hpp>
#include <sanguis/net/port.hpp>
#include <sanguis/main_object.hpp>
#include <fcppt/thread/object.hpp>
#include <fcppt/scoped_state_machine.hpp>
#include <fcppt/noncopyable.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/mainloop/io_service_scoped_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/thread/thread.hpp>
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
		net::port,
		load::context_base const &
	);

	void
	quit();

	awl::main::exit_code const
	run();

	bool
	running();

	~object();
private:
	void
	mainloop();

	void
	timer_callback();

	void
	reset_running();

	bool running_;

	awl::mainloop::io_service_scoped_ptr const io_service_;

	server::machine machine_;

	typedef fcppt::scoped_state_machine<
		server::machine
	> scoped_machine;

	scoped_machine scoped_machine_;

	boost::mutex mutex_;

	fcppt::thread::object server_thread_;
};

}
}

#endif
