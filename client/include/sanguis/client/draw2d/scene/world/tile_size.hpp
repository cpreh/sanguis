#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TILE_SIZE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TILE_SIZE_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/sprite/unit.hpp>
#include <sanguis/creator/difference_type.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_signed_fun.hpp>
#include <fcppt/type_traits/integral_cast.hpp>

namespace sanguis::client::draw2d::scene::world
{

using tile_size = fcppt::type_traits::integral_cast<
    sanguis::client::draw2d::scene::world::sprite::unit,
    fcppt::cast::size_fun,
    fcppt::type_traits::integral_cast<
        sanguis::creator::difference_type,
        fcppt::cast::to_signed_fun,
        sanguis::creator::tile_size>>;

}

#endif
