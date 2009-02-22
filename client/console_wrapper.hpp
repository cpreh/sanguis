#ifndef SANGUIS_CLIENT_MACHINE_CONSOLE_WRAPPER_HPP_INCLUDED
#define SANGUIS_CLIENT_MACHINE_CONSOLE_WRAPPER_HPP_INCLUDED

#include <sge/console/gfx_fwd.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/input/key_code.hpp> // TODO: declaration
#include <sge/input/key_pair.hpp> // TODO: declaration
#include <sge/input/callback.hpp>
#include <sge/signals/scoped_connection.hpp>

#include <boost/signals.hpp>

namespace sanguis
{
namespace client
{
struct console_wrapper
{
	sge::console::gfx &con;
	sge::signals::scoped_connection const ic;
	sge::input::key_code const toggler;
	boost::signal<sge::input::key_pair_fun> callbacks;

	console_wrapper(
		sge::console::gfx &,
		sge::input::system_ptr is,
		sge::input::key_code);

	void input_callback(
		sge::input::key_pair const &);

	sge::signals::scoped_connection register_callback(
		sge::input::callback);
};
}
}

#endif
