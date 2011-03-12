#ifndef SANGUIS_CLIENT_CONSOLE_HPP_INCLUDED
#define SANGUIS_CLIENT_CONSOLE_HPP_INCLUDED

#include "console_fwd.hpp"
#include "send_callback.hpp"
#include <sge/console/gfx_fwd.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/input/keyboard/device_ptr.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/keyboard/key_callback.hpp>
#include <sge/input/keyboard/key_function.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/string.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{

class console
{
	FCPPT_NONCOPYABLE(
		console
	);
public:
	explicit
	console(
		sge::console::gfx &,
		sge::input::keyboard::device_ptr,
		sge::input::keyboard::key_code::type toggler,
		send_callback const &
	);

	fcppt::signal::auto_connection 
	register_callback(
		sge::input::keyboard::key_callback const &
	);
	
	void
	register_server_command(
		fcppt::string const &name,
		fcppt::string const &description
	);
	
	sge::console::gfx &
	gfx();
	
	sge::console::gfx const &
	gfx() const;
private:
	void 
	input_callback(
		sge::input::keyboard::key_event const &
	);

	void
	server_callback(
		sge::console::arg_list const &
	);

	sge::console::gfx &gfx_;

	fcppt::signal::scoped_connection const input_connection_;

	sge::input::keyboard::key_code::type const toggler_;

	send_callback const send_;

	fcppt::signal::object<
		sge::input::keyboard::key_function
	> callbacks_;

	fcppt::signal::connection_manager server_connections_;
};

}
}

#endif
