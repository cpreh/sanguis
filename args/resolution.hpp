#ifndef SANGUIS_ARGS_RESOLUTIONG_HPP_INCLUDED
#define SANGUIS_ARGS_RESOLUTIONG_HPP_INCLUDED

#include "../resolution.hpp"
#include <boost/program_options/variables_map.hpp>

namespace sanguis
{
namespace args
{

sanguis::resolution const
resolution(
	boost::program_options::variables_map const &
);

}
}

#endif
