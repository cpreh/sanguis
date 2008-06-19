#ifndef SANGUIS_DRAW_COORD_TRANSFORM_HPP_INCLUDED
#define SANGUIS_DRAW_COORD_TRANSFORM_HPP_INCLUDED

#include "../messages/types.hpp"
#include <sge/sprite/types.hpp>
#include <sge/renderer/types.hpp>

namespace sanguis
{

sge::sprite::point const virtual_to_screen(const sge::renderer::screen_size_t &,const messages::pos_type &);
sge::sprite::dim const virtual_to_screen(const sge::renderer::screen_size_t &,const messages::dim_type &);
messages::pos_type const screen_to_virtual(const sge::renderer::screen_size_t &,const sge::sprite::point &);
messages::dim_type const screen_to_virtual(const sge::renderer::screen_size_t &,const sge::sprite::dim &);

}

#endif
