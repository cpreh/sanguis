#ifndef SANGUIS_ARGS_PARSE_HPP_INCLUDED
#define SANGUIS_ARGS_PARSE_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace args
{

boost::program_options::variables_map const
parse(
	int argc,
	char **argv,
	boost::program_options::options_description const &
);

}
}

#endif
