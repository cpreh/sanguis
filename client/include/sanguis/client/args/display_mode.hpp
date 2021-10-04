#ifndef SANGUIS_CLIENT_ARGS_DISPLAY_MODE_HPP_INCLUDED
#define SANGUIS_CLIENT_ARGS_DISPLAY_MODE_HPP_INCLUDED

#include <sanguis/client/args/result_fwd.hpp>
#include <sge/renderer/display_mode/optional_object_fwd.hpp>


namespace sanguis::client::args
{

sge::renderer::display_mode::optional_object
display_mode(
	sanguis::client::args::result const &
);

}

#endif
