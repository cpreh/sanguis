#ifndef SANGUIS_ARGS_RESOLUTION_HPP_INCLUDED
#define SANGUIS_ARGS_RESOLUTION_HPP_INCLUDED

#include "optional_resolution.hpp"
#include <boost/program_options/variables_map.hpp>

namespace sanguis
{
namespace args
{

args::optional_resolution const
resolution(
	boost::program_options::variables_map const &
);

}
}

#endif
