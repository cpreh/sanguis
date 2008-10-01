#ifndef SANGUIS_CLIENT_MACHINE_CONSOLE_WRAPPER_HPP_INCLUDED
#define SANGUIS_CLIENT_MACHINE_CONSOLE_WRAPPER_HPP_INCLUDED

#include <sge/console/console_gfx.hpp> // TODO: use a declaration!
#include <sge/input/system_fwd.hpp>
#include <sge/input/system.hpp>
#include <sge/input/key_type.hpp>
#include <sge/scoped_connection.hpp>

#include <boost/signals.hpp>

namespace sanguis
{
namespace client
{
struct console_wrapper
{
	sge::con::console_gfx &con;
	sge::scoped_connection ic;
	const sge::input::key_code toggler;
	boost::signal<sge::input::system::key_pair_fun> callbacks;

	console_wrapper(sge::con::console_gfx &,sge::input::system_ptr is,const sge::input::key_code);
	void input_callback(const sge::input::key_pair &);
	sge::scoped_connection register_callback(sge::input::system::callback);
};
}
}

#endif
