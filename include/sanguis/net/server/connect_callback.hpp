#ifndef SANGUIS_NET_SERVER_CONNECT_CALLBACK_HPP_INCLUDED
#define SANGUIS_NET_SERVER_CONNECT_CALLBACK_HPP_INCLUDED

#include <sanguis/net/server/connect_function.hpp>
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace net
{
namespace server
{

typedef fcppt::function::object<
	server::connect_function
> connect_callback;

}
}
}

#endif
