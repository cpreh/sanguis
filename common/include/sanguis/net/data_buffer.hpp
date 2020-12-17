#ifndef SANGUIS_NET_DATA_BUFFER_HPP_INCLUDED
#define SANGUIS_NET_DATA_BUFFER_HPP_INCLUDED

#include <alda/net/value_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace net
{

using
data_buffer
=
std::vector<
	alda::net::value_type
>;

}
}

#endif
