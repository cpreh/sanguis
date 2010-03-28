#ifndef SANGUIS_ARGS_RESOLUTION_HPP_INCLUDED
#define SANGUIS_ARGS_RESOLUTION_HPP_INCLUDED

#include "../resolution_type.hpp"
#include <boost/program_options/variables_map.hpp>

namespace sanguis
{
namespace args
{

sanguis::resolution_type const
resolution(
	boost::program_options::variables_map const &
);

}
}

#endif
