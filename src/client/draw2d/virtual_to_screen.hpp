#ifndef SANGUIS_CLIENT_DRAW2D_VIRTUAL_TO_SCREEN_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_VIRTUAL_TO_SCREEN_HPP_INCLUDED

#include "sprite/point.hpp"
#include "sprite/dim.hpp"
#include "../../messages/types/pos.hpp"
#include "../../messages/types/dim.hpp"
#include <sge/renderer/screen_size.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{

sprite::point const
virtual_to_screen(
	sge::renderer::screen_size const &,
	messages::types::pos const &
);

sprite::dim const
virtual_to_screen(
	sge::renderer::screen_size const &,
	messages::types::dim const &
);

}
}
}

#endif
