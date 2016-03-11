#ifndef SANGUIS_CLIENT_NET_SERIALIZE_TO_CIRCULAR_BUFFER_HPP_INCLUDED
#define SANGUIS_CLIENT_NET_SERIALIZE_TO_CIRCULAR_BUFFER_HPP_INCLUDED

#include <sanguis/messages/client/base_fwd.hpp>
#include <alda/net/buffer/circular_send/streambuf_fwd.hpp>
#include <fcppt/preprocessor/warn_unused_result.hpp>


namespace sanguis
{
namespace client
{
namespace net
{

bool
serialize_to_circular_buffer(
	sanguis::messages::client::base const &,
	alda::net::buffer::circular_send::streambuf &
)
FCPPT_PP_WARN_UNUSED_RESULT;

}
}
}

#endif
