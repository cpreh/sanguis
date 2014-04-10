#ifndef SANGUIS_SERVER_TIMER_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_TIMER_CALLBACK_HPP_INCLUDED

#include <sanguis/server/timer_function.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{

typedef std::function<
	sanguis::server::timer_function
> timer_callback;

}
}

#endif
