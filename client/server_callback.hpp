#ifndef SANGUIS_CLIENT_SERVER_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_SERVER_CALLBACK_HPP_INCLUDED

#include "../net/port_type.hpp"
#include <sge/function/object_fwd.hpp>

namespace sanguis
{
namespace client
{

typedef sge::function::object<
	void (
		net::port_type
	)
> server_callback;

}
}

#endif // SANGUIS_CLIENT_SERVER_CALLBACK_HPP_INCLUDED
