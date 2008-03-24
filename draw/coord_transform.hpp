#ifndef SANGUIS_DRAW_COORD_TRANSFORM_HPP_INCLUDED
#define SANGUIS_DRAW_COORD_TRANSFORM_HPP_INCLUDED

#include "../messages/types.hpp"
#include <sge/sprite/types.hpp>
#include <sge/renderer/types.hpp>

namespace sanguis
{
sge::sprite_point virtual_to_screen(const sge::screen_size_t &,const messages::pos_type &);
sge::sprite_dim virtual_to_screen(const sge::screen_size_t &,const messages::dim_type &);
messages::pos_type screen_to_virtual(const sge::screen_size_t &,const sge::sprite_point &);
messages::dim_type screen_to_virtual(const sge::screen_size_t &,const sge::sprite_dim &);
}

#endif
