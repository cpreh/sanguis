#include "console_wrapper.hpp"
#include <boost/bind.hpp>

sanguis::client::console_wrapper::console_wrapper(sge::con::console_gfx &con,sge::input_system_ptr is,const sge::key_code toggler)
	: con(con),
	  ic(is->register_callback(boost::bind(&console_wrapper::input_callback,this,_1))),
		toggler(toggler) {}

void sanguis::client::console_wrapper::input_callback(const sge::key_pair &k)
{
	if (k.key().code() == toggler && !sge::math::almost_zero(k.value()))
	{
		con.toggle();
		return;
	}

	if (con.active())
		con.key_callback(k);
	else
		callbacks(k);
}

sge::scoped_connection sanguis::client::console_wrapper::register_callback(sge::input_system::callback c)
{
	return callbacks.connect(c);
}
