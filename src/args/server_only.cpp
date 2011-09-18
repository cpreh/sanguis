#include <sanguis/args/server_only.hpp>

bool
sanguis::args::server_only(
	boost::program_options::variables_map const &_vm
)
{
	return
		_vm["serveronly"].as<
			bool
		>();
}
