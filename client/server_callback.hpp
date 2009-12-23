#ifndef SANGUIS_CLIENT_SERVER_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_SERVER_CALLBACK_HPP_INCLUDED

#include "../net/port_type.hpp"
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace client
{

typedef fcppt::function::object<
	void (
		net::port_type
	)
> server_callback;

}
}

#endif // SANGUIS_CLIENT_SERVER_CALLBACK_HPP_INCLUDED
