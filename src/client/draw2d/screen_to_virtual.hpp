#ifndef SANGUIS_CLIENT_DRAW2D_SCREEN_TO_VIRTUAL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCREEN_TO_VIRTUAL_HPP_INCLUDED

#include "sprite/point.hpp"
#include "../../messages/types/vector2.hpp"

namespace sanguis
{
namespace client
{
namespace draw2d
{

sanguis::messages::types::vector2 const
screen_to_virtual(
	sprite::point const &
);

}
}
}

#endif
