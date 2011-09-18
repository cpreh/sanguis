#ifndef SANGUIS_ARGS_LOG_LEVEL_HPP_INCLUDED
#define SANGUIS_ARGS_LOG_LEVEL_HPP_INCLUDED

#include <fcppt/log/level.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>

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
