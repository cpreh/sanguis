#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_FADE_TYPE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_FADE_TYPE_HPP_INCLUDED

#include "fade_time_range.hpp"
#include <fcppt/optional_fwd.hpp>

namespace sanguis 
{
namespace client
{
namespace draw2d
{
namespace particle
{

typedef fcppt::optional<
	fade_time_range
> fade_type;

}
}
}
}

#endif
