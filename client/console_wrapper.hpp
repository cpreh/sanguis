#ifndef SANGUIS_CLIENT_MACHINE_CONSOLE_WRAPPER_HPP_INCLUDED
#define SANGUIS_CLIENT_MACHINE_CONSOLE_WRAPPER_HPP_INCLUDED

#include <sge/console/console_gfx.hpp>
#include <sge/input/input_system.hpp>

#include <boost/signals.hpp>

namespace sanguis
{
namespace client
{
struct console_wrapper
{
	sge::con::console_gfx &con;
	sge::scoped_connection ic;
	const sge::key_code toggler;
	boost::signal<sge::input_system::key_pair_fun> callbacks;

	console_wrapper(sge::con::console_gfx &,sge::input_system_ptr is,const sge::key_code);
	void input_callback(const sge::key_pair &);
	sge::scoped_connection register_callback(sge::input_system::callback);
};
}
}

#endif
