#ifndef SANGUIS_CLIENT_SERVER_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_SERVER_CALLBACK_HPP_INCLUDED

#include <alda/net/port.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis
{
namespace client
{

typedef
fcppt::function<
	void (
		alda::net::port
	)
>
server_callback;

}
}

#endif
