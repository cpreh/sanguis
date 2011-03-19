#ifndef SANGUIS_NET_CLIENT_ERROR_CALLBACK_HPP_INCLUDED
#define SANGUIS_NET_CLIENT_ERROR_CALLBACK_HPP_INCLUDED

#include "error_function.hpp"
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace net
{
namespace client
{

typedef fcppt::function::object<
	client::error_function
> error_callback;

}
}
}

#endif
