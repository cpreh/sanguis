#ifndef NET_IS_DISCONNECT_HPP_INCLUDED
#define NET_IS_DISCONNECT_HPP_INCLUDED

#include <boost/system/error_code.hpp>

// those are "soft" disconnects, so not to be called as errors but as
// "normal" disconnects :)

namespace net
{

bool is_disconnect(const boost::system::error_code &e);

}
#endif
