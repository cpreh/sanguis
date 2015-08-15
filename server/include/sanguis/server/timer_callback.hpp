#ifndef SANGUIS_SERVER_TIMER_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_TIMER_CALLBACK_HPP_INCLUDED

#include <sanguis/server/timer_function.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis
{
namespace server
{

typedef
fcppt::function<
	sanguis::server::timer_function
>
timer_callback;

}
}

#endif
