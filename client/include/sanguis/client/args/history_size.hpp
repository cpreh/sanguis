#ifndef SANGUIS_CLIENT_ARGS_HISTORY_SIZE_HPP_INCLUDED
#define SANGUIS_CLIENT_ARGS_HISTORY_SIZE_HPP_INCLUDED

#include <sge/console/gfx/output_line_limit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace args
{

sge::console::gfx::output_line_limit
history_size(
	boost::program_options::variables_map const &
);

}
}
}

#endif
