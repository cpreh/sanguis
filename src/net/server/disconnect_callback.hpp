#ifndef SANGUIS_NET_SERVER_DISCONNECT_CALLBACK_HPP_INCLUDED
#define SANGUIS_NET_SERVER_DISCONNECT_CALLBACK_HPP_INCLUDED

#include "disconnect_function.hpp"
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace net
{
namespace server
{

typedef fcppt::function::object<
	server::disconnect_function
> disconnect_callback;

}
}
}

#endif
