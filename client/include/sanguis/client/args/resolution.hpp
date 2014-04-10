#ifndef SANGUIS_CLIENT_ARGS_RESOLUTION_HPP_INCLUDED
#define SANGUIS_CLIENT_ARGS_RESOLUTION_HPP_INCLUDED

#include <sanguis/client/args/optional_resolution.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace args
{

sanguis::client::args::optional_resolution const
resolution(
	boost::program_options::variables_map const &
);

}
}
}

#endif
