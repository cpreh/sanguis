#ifndef SANGUIS_ARGS_WINDOW_MODE_HPP_INCLUDED
#define SANGUIS_ARGS_WINDOW_MODE_HPP_INCLUDED

#include <sge/renderer/window_mode.hpp>
#include <boost/program_options/variables_map.hpp>

namespace sanguis
{
namespace args
{

sge::renderer::window_mode::type
window_mode(
	boost::program_options::variables_map const &
);

}
}

#endif
