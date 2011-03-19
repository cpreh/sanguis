#include "parse.hpp"
#include <boost/program_options/parsers.hpp>

boost::program_options::variables_map const
sanguis::args::parse(
	int const _argc,
	char **const _argv,
	boost::program_options::options_description const &_desc
)
{
	namespace po = boost::program_options;

	po::variables_map vm;

	po::store(
		po::parse_command_line(
			_argc,
			_argv,
			_desc
		),
		vm
	);

	po::notify(
		vm
	);

	return vm;
}
