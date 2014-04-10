#ifndef SANGUIS_CLIENT_ARGS_LOG_LEVEL_HPP_INCLUDED
#define SANGUIS_CLIENT_ARGS_LOG_LEVEL_HPP_INCLUDED

#include <sanguis/client/symbol.hpp>
#include <fcppt/log/level_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace args
{

SANGUIS_CLIENT_SYMBOL
fcppt::log::level
log_level(
	boost::program_options::variables_map const &
);

}
}
}

#endif
