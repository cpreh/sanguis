#ifndef SANGUIS_SERVER_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_OBJECT_HPP_INCLUDED

#include "machine.hpp"
#include "object_fwd.hpp"
#include "../load/context_base_fwd.hpp"
#include "../net/port.hpp"
#include "../main_object.hpp"
#include <fcppt/thread/object.hpp>
#include <fcppt/scoped_state_machine.hpp>
#include <fcppt/noncopyable.hpp>
#include <awl/mainloop/io_service_scoped_ptr.hpp>
#include <boost/thread/thread.hpp>

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

	int
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

	awl::mainloop::io_service_scoped_ptr const io_service_;

	server::machine machine_;

	bool running_;

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
