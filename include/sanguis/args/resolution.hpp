#ifndef SANGUIS_ARGS_RESOLUTION_HPP_INCLUDED
#define SANGUIS_ARGS_RESOLUTION_HPP_INCLUDED

#include <sanguis/args/optional_resolution_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace args
{

sanguis::args::optional_resolution const
resolution(
	boost::program_options::variables_map const &
);

}
}

#endif
