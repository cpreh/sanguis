#ifndef SANGUIS_ARGS_PARSE_HPP_INCLUDED
#define SANGUIS_ARGS_PARSE_HPP_INCLUDED

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>

namespace sanguis
{
namespace args
{

boost::program_options::variables_map const
parse(
	int argv,
	char const *const *argv,
	boost::program_options::options_description const &
);

}
}

#endif
