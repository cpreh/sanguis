#ifndef SANGUIS_NET_CLIENT_DISCONNECT_CALLBACK_HPP_INCLUDED
#define SANGUIS_NET_CLIENT_DISCONNECT_CALLBACK_HPP_INCLUDED

#include "disconnect_function.hpp"
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace net
{
namespace client
{

typedef fcppt::function::object<
	client::disconnect_function
> disconnect_callback;

}
}
}

#endif
