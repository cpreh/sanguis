#ifndef SANGUIS_ARGS_SERVER_PORT_HPP_INCLUDED
#define SANGUIS_ARGS_SERVER_PORT_HPP_INCLUDED

#include <alda/net/port.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace args
{

alda::net::port const
server_port(
	boost::program_options::variables_map const &
);

}
}

#endif
