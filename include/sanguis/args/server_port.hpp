#ifndef SANGUIS_ARGS_SERVER_PORT_HPP_INCLUDED
#define SANGUIS_ARGS_SERVER_PORT_HPP_INCLUDED

#include <sanguis/net/port.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace args
{

net::port
server_port(
	boost::program_options::variables_map const &
);

}
}

#endif
