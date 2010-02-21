#include "server_port.hpp"

sanguis::net::port_type
sanguis::args::server_port(
	boost::program_options::variables_map const &vm
)
{
	return
		vm["serverport"].as<
			net::port_type
		>();
}
