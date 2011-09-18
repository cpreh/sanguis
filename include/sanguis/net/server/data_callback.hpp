#ifndef SANGUIS_NET_SERVER_DATA_CALLBACK_HPP_INCLUDED
#define SANGUIS_NET_SERVER_DATA_CALLBACK_HPP_INCLUDED

#include <sanguis/net/server/data_function.hpp>
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace net
{
namespace server
{

typedef fcppt::function::object<
	server::data_function
> data_callback;

}
}
}

#endif
