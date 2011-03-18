#ifndef SANGUIS_NET_CLIENT_ERROR_FUNCTION_HPP_INCLUDED
#define SANGUIS_NET_CLIENT_ERROR_FUNCTION_HPP_INCLUDED

#include <fcppt/string.hpp>
#include <boost/system/error_code.hpp>

namespace sanguis
{
namespace net
{
namespace client
{

typedef void
error_function(
	fcppt::string const &,
	boost::system::error_code
);

}
}
}

#endif
