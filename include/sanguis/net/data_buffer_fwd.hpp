#ifndef SANGUIS_NET_DATA_BUFFER_FWD_HPP_INCLUDED
#define SANGUIS_NET_DATA_BUFFER_FWD_HPP_INCLUDED

#include <alda/net/value_type.hpp>
#include <fcppt/container/raw_vector_fwd.hpp>


namespace sanguis
{
namespace net
{

typedef
fcppt::container::raw_vector<
	alda::net::value_type
>
data_buffer;

}
}

#endif
