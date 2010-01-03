#ifndef SANGUIS_DRAW_COORD_TRANSFORM_HPP_INCLUDED
#define SANGUIS_DRAW_COORD_TRANSFORM_HPP_INCLUDED

#include "sprite/point.hpp"
#include "sprite/dim.hpp"
#include "../messages/types/pos.hpp"
#include "../messages/types/dim.hpp"
#include <sge/renderer/screen_size.hpp>

namespace sanguis
{
namespace draw
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

#endif
