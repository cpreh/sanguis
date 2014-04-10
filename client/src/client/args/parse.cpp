#include <sanguis/client/args/parse.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


boost::program_options::variables_map
sanguis::client::args::parse(
	int const _argc,
	char **const _argv,
	boost::program_options::options_description const &_desc
)
{
	boost::program_options::variables_map vm;

	boost::program_options::store(
		boost::program_options::parse_command_line(
			_argc,
			_argv,
			_desc
		),
		vm
	);

	boost::program_options::notify(
		vm
	);

	return vm;
}
