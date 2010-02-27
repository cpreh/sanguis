#include "server_only.hpp"

bool
sanguis::args::server_only(
	boost::program_options::variables_map const &vm
)
{
	return vm["serveronly"].as<bool>();
}
