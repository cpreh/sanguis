#ifndef SANGUIS_CLIENT_DRAW2D_SCREEN_TO_VIRTUAL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCREEN_TO_VIRTUAL_HPP_INCLUDED

#include "sprite/point.hpp"
#include "sprite/dim.hpp"
#include "../messages/types/pos.hpp"
#include "../messages/types/dim.hpp"
#include <sge/renderer/screen_size.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{

messages::types::pos const
screen_to_virtual(
	sge::renderer::screen_size const &,
	sprite::point const &
);

messages::types::dim const
screen_to_virtual(
	sge::renderer::screen_size const &,
	sprite::dim const &
);

}
}
}

#endif
