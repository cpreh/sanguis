#ifndef SANGUIS_NET_CLIENT_DATA_CALLBACK_HPP_INCLUDED
#define SANGUIS_NET_CLIENT_DATA_CALLBACK_HPP_INCLUDED

#include "data_function.hpp"
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace net
{
namespace client
{

typedef fcppt::function::object<
	client::data_function
> data_callback;

}
}
}

#endif
