#ifndef SANGUIS_NET_SERVER_DISCONNECT_FUNCTION_HPP_INCLUDED
#define SANGUIS_NET_SERVER_DISCONNECT_FUNCTION_HPP_INCLUDED

#include <sanguis/net/id.hpp>
#include <fcppt/string.hpp>

namespace sanguis
{
namespace net
{
namespace server
{

typedef void
disconnect_function(
	net::id,
	fcppt::string const &
);

}
}
}

#endif
