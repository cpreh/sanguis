#ifndef SANGUIS_NET_MESSAGE_SIZE_HPP_INCLUDED
#define SANGUIS_NET_MESSAGE_SIZE_HPP_INCLUDED

#include <sanguis/common/symbol.hpp>
#include <alda/net/size_type.hpp>


namespace sanguis
{
namespace net
{

SANGUIS_COMMON_SYMBOL
alda::net::size_type
message_size(
	alda::net::size_type body_size
);

}
}

#endif
