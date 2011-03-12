#ifndef SANGUIS_ARGS_LOG_LEVEL_HPP_INCLUDED
#define SANGUIS_ARGS_LOG_LEVEL_HPP_INCLUDED

#include <fcppt/log/level.hpp>
#include <boost/program_options/variables_map.hpp>

namespace sanguis
{
namespace args
{

fcppt::log::level::type
log_level(
	boost::program_options::variables_map const &
);

}
}

#endif
