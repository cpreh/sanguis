#ifndef SANGUIS_CLIENT_DRAW2D_SUNLIGHT_SUN_ANGLE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SUNLIGHT_SUN_ANGLE_HPP_INCLUDED

#include <sanguis/client/draw2d/sunlight/real.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ctime>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sunlight
{

sunlight::real
sun_angle(
	std::tm const &
);

}
}
}
}

#endif
