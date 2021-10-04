#ifndef SANGUIS_SERVER_TIMER_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_TIMER_CALLBACK_HPP_INCLUDED

#include <sanguis/server/timer_function.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis::server
{

using
timer_callback
=
fcppt::function<
	sanguis::server::timer_function
>;

}

#endif
