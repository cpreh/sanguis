#include "parse.hpp"
#include "parse.hpp"
#include <fcppt/filesystem/exists.hpp>
#include <fcppt/text.hpp>
#include <iostream>
#include <ostream>
#include <fstream>

boost::program_options::variables_map const
sanguis::args::parse(
	int const argv,
	char const *const *const argv,
	boost::program_options::options_description const &desc
)
{
	namespace po = boost::program_options;

	po::variables_map vm;

	po::store(
		po::parse_command_line(
			argc,
			argv,
			desc
		),
		vm
	);

	if(
		fcppt::filesystem::exists(
			FCPPT_TEXT("config")
		)
	)
	{
		// NOTE: this has to be a std::ifstream since boost::po only handels those cases
		std::ifstream config_file("config");
		// highly unlikely to happen
		if (!config_file.is_open())
			std::cerr << "couldn't open config file\n";
		else
			po::store(
				po::parse_config_file(
					config_file,
					desc
				),
				vm
			);
	}

	po::notify(vm);

	return vm;
}
