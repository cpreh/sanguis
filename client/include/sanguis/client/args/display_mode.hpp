#ifndef SANGUIS_CLIENT_ARGS_DISPLAY_MODE_HPP_INCLUDED
#define SANGUIS_CLIENT_ARGS_DISPLAY_MODE_HPP_INCLUDED

#include <sge/renderer/display_mode/optional_object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace args
{

sge::renderer::display_mode::optional_object
display_mode(
	boost::program_options::variables_map const &
);

}
}
}

#endif
