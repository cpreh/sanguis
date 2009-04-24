#ifndef SANGUIS_CLIENT_CONSOLE_WRAPPER_HPP_INCLUDED
#define SANGUIS_CLIENT_CONSOLE_WRAPPER_HPP_INCLUDED

#include <sge/console/gfx_fwd.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/input/key_code.hpp>
#include <sge/input/key_pair_fwd.hpp>
#include <sge/input/callback.hpp>
#include <sge/signal/object.hpp>
#include <sge/signal/auto_connection.hpp>
#include <sge/signal/scoped_connection.hpp>

namespace sanguis
{
namespace client
{
struct console_wrapper
{
	sge::console::gfx &con;
	sge::signal::scoped_connection const ic;
	sge::input::key_code const toggler;
	sge::signal::object<sge::input::key_pair_fun> callbacks;

	console_wrapper(
		sge::console::gfx &,
		sge::input::system_ptr is,
		sge::input::key_code);

	void input_callback(
		sge::input::key_pair const &);

	sge::signal::auto_connection register_callback(
		sge::input::callback);
};
}
}

#endif
