#ifndef SANGUIS_DRAW_COORD_TRANSFORM_HPP_INCLUDED
#define SANGUIS_DRAW_COORD_TRANSFORM_HPP_INCLUDED

#include "../messages/types.hpp"
#include <sge/sprite/point.hpp>
#include <sge/sprite/dim.hpp>
#include <sge/renderer/screen_size.hpp>

namespace sanguis
{

sge::sprite::point const
virtual_to_screen(
	sge::renderer::screen_size_t const &,
	messages::pos_type const &);

sge::sprite::dim const
virtual_to_screen(
	sge::renderer::screen_size_t const &,
	messages::dim_type const &);

messages::pos_type const
screen_to_virtual(
	sge::renderer::screen_size_t const &,
	sge::sprite::point const &);

messages::dim_type const
screen_to_virtual(
	sge::renderer::screen_size_t const &,
	sge::sprite::dim const &);

}

#endif
