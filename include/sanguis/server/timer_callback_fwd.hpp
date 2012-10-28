#ifndef SANGUIS_SERVER_TIMER_CALLBACK_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_TIMER_CALLBACK_FWD_HPP_INCLUDED

#include <sanguis/server/timer_function.hpp>
#include <fcppt/function/object_fwd.hpp>


namespace sanguis
{
namespace server
{

typedef fcppt::function::object<
	sanguis::server::timer_function
> timer_callback;

}
}

#endif
