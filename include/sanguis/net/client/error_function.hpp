#ifndef SANGUIS_NET_CLIENT_ERROR_FUNCTION_HPP_INCLUDED
#define SANGUIS_NET_CLIENT_ERROR_FUNCTION_HPP_INCLUDED

#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/system/error_code.hpp>
#include <fcppt/config/external_end.hpp>

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
