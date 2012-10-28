#ifndef SANGUIS_NET_MESSAGE_SIZE_HPP_INCLUDED
#define SANGUIS_NET_MESSAGE_SIZE_HPP_INCLUDED

#include <alda/net/size_type.hpp>


namespace sanguis
{
namespace net
{

alda::net::size_type
message_size(
	alda::net::size_type body_size
);

}
}

#endif
