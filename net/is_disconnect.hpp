#ifndef NET_IS_DISCONNECT_HPP_INCLUDED
#define NET_IS_DISCONNECT_HPP_INCLUDED

#include <asio.hpp>

// those are "soft" disconnects, so not to be called as errors but as
// "normal" disconnects :)
inline bool is_disconnect(const asio::error_code &e)
{
	return e == asio::error::connection_aborted || e == asio::error::connection_reset ||
				 e == asio::error::network_reset || e == asio::error::timed_out || 
				 e == asio::error::eof;
}

#endif
