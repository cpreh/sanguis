#ifndef SANGUIS_ARGS_SERVER_PORT_HPP_INCLUDED
#define SANGUIS_ARGS_SERVER_PORT_HPP_INCLUDED

#include "../net/port_type.hpp"
#include <boost/program_options/variables_map.hpp>

namespace sanguis
{
namespace args
{

net::port_type
server_port(
	boost::program_options::variables_map const &
);

}
}

#endif
