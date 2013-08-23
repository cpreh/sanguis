#include <sanguis/args/server_only.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


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
