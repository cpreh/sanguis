#ifndef SANGUIS_NET_CLIENT_CONNECT_CALLBACK_HPP_INCLUDED
#define SANGUIS_NET_CLIENT_CONNECT_CALLBACK_HPP_INCLUDED

#include <sanguis/net/client/connect_function.hpp>
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace net
{
namespace client
{

typedef fcppt::function::object<
	client::connect_function
> connect_callback;

}
}
}

#endif
