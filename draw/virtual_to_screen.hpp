#ifndef SANGUIS_DRAW_VIRTUAL_TO_SCREEN_HPP_INCLUDED
#define SANGUIS_DRAW_VIRTUAL_TO_SCREEN_HPP_INCLUDED

#include "../messages/types.hpp"
#include <sge/sprite/types.hpp>
#include <sge/renderer/types.hpp>

namespace sanguis
{
sge::sprite_point virtual_to_screen(const sge::screen_size_t &,const messages::pos_type &);
sge::sprite_dim virtual_to_screen(const sge::screen_size_t &,const messages::dim_type &);
}

#endif
