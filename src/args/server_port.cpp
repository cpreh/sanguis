#include <sanguis/args/server_port.hpp>

sanguis::net::port
sanguis::args::server_port(
	boost::program_options::variables_map const &_vm
)
{
	return
		_vm["serverport"].as<
			net::port
		>();
}
