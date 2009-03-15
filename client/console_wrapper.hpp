#ifndef SANGUIS_CLIENT_MACHINE_CONSOLE_WRAPPER_HPP_INCLUDED
#define SANGUIS_CLIENT_MACHINE_CONSOLE_WRAPPER_HPP_INCLUDED

#include <sge/console/gfx_fwd.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/input/key_code.hpp> // TODO: declaration
#include <sge/input/key_pair.hpp> // TODO: declaration
#include <sge/input/callback.hpp>
#include <sge/signals/signal.hpp>
#include <sge/signals/connection.hpp>

namespace sanguis
{
namespace client
{
struct console_wrapper
{
	sge::console::gfx &con;
	sge::signals::auto_connection ic;
	sge::input::key_code const toggler;
	sge::signals::signal<sge::input::key_pair_fun> callbacks;

	console_wrapper(
		sge::console::gfx &,
		sge::input::system_ptr is,
		sge::input::key_code);

	void input_callback(
		sge::input::key_pair const &);

	sge::signals::auto_connection register_callback(
		sge::input::callback);
};
}
}

#endif
