#ifndef SANGUIS_CLIENT_SERVER_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_SERVER_CALLBACK_HPP_INCLUDED

#include <alda/net/port.hpp>
#include <fcppt/function/object_fwd.hpp>


namespace sanguis
{
namespace client
{

typedef fcppt::function::object<
	void (
		alda::net::port
	)
> server_callback;

}
}

#endif
