#ifndef SANGUIS_CLIENT_ARGS_OPTIONAL_RESOLUTION_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_ARGS_OPTIONAL_RESOLUTION_FWD_HPP_INCLUDED

#include <sge/renderer/screen_size_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace args
{

typedef
fcppt::optional<
	sge::renderer::screen_size
>
optional_resolution;

}
}
}

#endif