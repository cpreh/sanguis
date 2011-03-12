#ifndef SANGUIS_ARGS_SCREEN_MODE_HPP_INCLUDED
#define SANGUIS_ARGS_SCREEN_MODE_HPP_INCLUDED

#include <sge/renderer/screen_mode.hpp>
#include <boost/program_options/variables_map.hpp>

namespace sanguis
{
namespace args
{

sge::renderer::screen_mode const
screen_mode(
	boost::program_options::variables_map const &
);

}
}

#endif
