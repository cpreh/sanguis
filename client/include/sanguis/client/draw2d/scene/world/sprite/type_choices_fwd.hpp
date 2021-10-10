#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_TYPE_CHOICES_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_TYPE_CHOICES_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/sprite/unit.hpp>
#include <sge/sprite/config/float_type_fwd.hpp>
#include <sge/sprite/config/type_choices_fwd.hpp>
#include <sge/sprite/config/unit_type_fwd.hpp>

namespace sanguis::client::draw2d::scene::world::sprite
{

using type_choices = sge::sprite::config::type_choices<
    sge::sprite::config::unit_type<sanguis::client::draw2d::scene::world::sprite::unit>,
    sge::sprite::config::float_type<float // don't care
                                    >>;

}

#endif
