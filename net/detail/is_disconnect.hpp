#ifndef SANGUIS_NET_DETAIL_IS_DISCONNECT_HPP_INCLUDED
#define SANGUIS_NET_DETAIL_IS_DISCONNECT_HPP_INCLUDED

#include <boost/system/error_code.hpp>

// those are "soft" disconnects, so not to be called as errors but as
// "normal" disconnects :)

namespace sanguis
{
namespace net
{
namespace detail
{

bool is_disconnect(boost::system::error_code const &e);

}
}
}

#endif
