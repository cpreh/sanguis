#ifndef SANGUIS_CLIENT_DRAW2D_VIRTUAL_TO_SCREEN_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_VIRTUAL_TO_SCREEN_HPP_INCLUDED

#include "sprite/point.hpp"
#include "../../messages/types/vector2.hpp"

namespace sanguis
{
namespace client
{
namespace draw2d
{

sprite::point const
virtual_to_screen(
	messages::types::vector2 const &
);

}
}
}

#endif
