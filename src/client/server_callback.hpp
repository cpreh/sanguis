#ifndef SANGUIS_CLIENT_SERVER_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_SERVER_CALLBACK_HPP_INCLUDED

#include "../net/port.hpp"
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace client
{

typedef fcppt::function::object<
	void (
		net::port
	)
> server_callback;

}
}

#endif // SANGUIS_CLIENT_SERVER_CALLBACK_HPP_INCLUDED
