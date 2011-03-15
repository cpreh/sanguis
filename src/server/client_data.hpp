#ifndef SANGUIS_SERVER_CLIENT_DATA_HPP_INCLUDED
#define SANGUIS_SERVER_CLIENT_DATA_HPP_INCLUDED

#include "../net/data_type.hpp"
#include <fcppt/container/raw_vector_decl.hpp>

namespace sanguis
{
namespace server
{

struct client_data
{
	net::data_type in_buffer;
	net::data_type out_buffer;
};

}
}

#endif
