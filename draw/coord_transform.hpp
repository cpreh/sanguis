#ifndef SANGUIS_DRAW_COORD_TRANSFORM_HPP_INCLUDED
#define SANGUIS_DRAW_COORD_TRANSFORM_HPP_INCLUDED

#include "../messages/types/pos.hpp"
#include "../messages/types/dim.hpp"
#include <sge/sprite/point.hpp>
#include <sge/sprite/dim.hpp>
#include <sge/renderer/screen_size.hpp>

namespace sanguis
{

sge::sprite::point const
virtual_to_screen(
	sge::renderer::screen_size const &,
	messages::types::pos const &);

sge::sprite::dim const
virtual_to_screen(
	sge::renderer::screen_size const &,
	messages::types::dim const &);

messages::types::pos const
screen_to_virtual(
	sge::renderer::screen_size const &,
	sge::sprite::point const &);

messages::types::dim const
screen_to_virtual(
	sge::renderer::screen_size const &,
	sge::sprite::dim const &);

}

#endif
