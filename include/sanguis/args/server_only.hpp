#ifndef SANGUIS_ARGS_SERVER_ONLY_HPP_INCLUDED
#define SANGUIS_ARGS_SERVER_ONLY_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace args
{

bool
server_only(
	boost::program_options::variables_map const &
);

}
}

#endif
