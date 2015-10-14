#ifndef SANGUIS_CLIENT_ARGS_DRAW_DEBUG_HPP_INCLUDED
#define SANGUIS_CLIENT_ARGS_DRAW_DEBUG_HPP_INCLUDED

#include <sanguis/client/draw/debug.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace args
{

sanguis::client::draw::debug
draw_debug(
	boost::program_options::variables_map const &
);

}
}
}

#endif
