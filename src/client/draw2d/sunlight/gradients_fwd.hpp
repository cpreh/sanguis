#ifndef SANGUIS_CLIENT_DRAW2D_SUNLIGHT_GRADIENTS_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SUNLIGHT_GRADIENTS_FWD_HPP_INCLUDED

#include "basic_gradients_fwd.hpp"
#include "real.hpp"
#include "rgb32f_format.hpp"

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sunlight
{

typedef sunlight::basic_gradients<
	rgb32f_format,
	real,
	real
> gradients;

}
}
}
}

#endif
