#include "console_wrapper.hpp"
#include <sge/console/gfx.hpp>
#include <sge/input/system.hpp>
#include <sge/input/key_pair.hpp>
#include <fcppt/tr1/functional.hpp>

sanguis::client::console_wrapper::console_wrapper(
	sge::console::gfx &con,
	sge::input::system_ptr const is,
	sge::input::key_code const toggler
)
:
	con(con),
	ic(
		is->register_callback(
			std::tr1::bind(
				&console_wrapper::input_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	toggler(toggler)
{}

void
sanguis::client::console_wrapper::input_callback(
	sge::input::key_pair const &k
)
{
	if (k.key().code() == toggler && k.value() != 0)
	{
		con.active(!con.active());
		return;
	}

	if (!con.active())
		callbacks(k);
}

fcppt::signal::auto_connection
sanguis::client::console_wrapper::register_callback(
	sge::input::callback const c
)
{
	return callbacks.connect(c);
}
