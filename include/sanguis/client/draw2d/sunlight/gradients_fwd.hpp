#ifndef SANGUIS_CLIENT_DRAW2D_SUNLIGHT_GRADIENTS_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SUNLIGHT_GRADIENTS_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/sunlight/basic_gradients_fwd.hpp>
#include <sanguis/client/draw2d/sunlight/real.hpp>
#include <sanguis/client/draw2d/sunlight/rgb32f_format.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sunlight
{

typedef sanguis::client::draw2d::sunlight::basic_gradients<
	sanguis::client::draw2d::sunlight::rgb32f_format,
	sanguis::client::draw2d::sunlight::real,
	sanguis::client::draw2d::sunlight::real
> gradients;

}
}
}
}

#endif
