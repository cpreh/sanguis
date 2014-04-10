#ifndef SANGUIS_NET_MESSAGE_HEADER_SIZE_HPP_INCLUDED
#define SANGUIS_NET_MESSAGE_HEADER_SIZE_HPP_INCLUDED

#include <sanguis/net/message_header.hpp>
#include <alda/net/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/integral_c.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace net
{

typedef boost::mpl::integral_c<
	alda::net::size_type,
	sizeof(
		sanguis::net::message_header
	)
> message_header_size;

}
}

#endif
