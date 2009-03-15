#include "console_wrapper.hpp"
#include <sge/math/compare.hpp>
#include <sge/console/gfx.hpp>
#include <sge/input/system.hpp>
#include <boost/bind.hpp>

sanguis::client::console_wrapper::console_wrapper(
	sge::console::gfx &con,
	sge::input::system_ptr const is,
	sge::input::key_code const toggler)
:
	con(con),
	ic(
		is->register_callback(
			boost::bind(
				&console_wrapper::input_callback,
				this,
				_1))),
	toggler(toggler)
{}

void sanguis::client::console_wrapper::input_callback(
	sge::input::key_pair const &k)
{
	if (k.key().code() == toggler && !sge::math::almost_zero(k.value()))
	{
		con.active(!con.active());
		return;
	}

	if (!con.active())
		callbacks(k);
}

sge::signal::auto_connection
sanguis::client::console_wrapper::register_callback(
	sge::input::callback const c)
{
	return callbacks.connect(c);
}
