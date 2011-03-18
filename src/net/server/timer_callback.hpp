#ifndef SANGUIS_NET_SERVER_TIMER_CALLBACK_HPP_INCLUDED
#define SANGUIS_NET_SERVER_TIMER_CALLBACK_HPP_INCLUDED

#include "timer_function.hpp"
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace net
{
namespace server
{

typedef fcppt::function::object<
	server::timer_function
> timer_callback;

}
}
}

#endif
