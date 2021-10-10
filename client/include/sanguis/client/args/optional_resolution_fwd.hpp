#ifndef SANGUIS_CLIENT_ARGS_OPTIONAL_RESOLUTION_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_ARGS_OPTIONAL_RESOLUTION_FWD_HPP_INCLUDED

#include <sge/renderer/screen_size_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>

namespace sanguis::client::args
{

using optional_resolution = fcppt::optional::object<sge::renderer::screen_size>;

}

#endif
