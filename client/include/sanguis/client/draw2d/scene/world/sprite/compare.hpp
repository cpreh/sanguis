#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_COMPARE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_COMPARE_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/sprite/is_background_role.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/object.hpp>
#include <sge/sprite/compare/default.hpp>

namespace sanguis::client::draw2d::scene::world::sprite
{

struct compare
{
  bool operator()(
      sanguis::client::draw2d::scene::world::sprite::object const &_left,
      sanguis::client::draw2d::scene::world::sprite::object const &_right) const
  {
    bool const left_is_background(
        _left.get<sanguis::client::draw2d::scene::world::sprite::is_background_role>());

    bool const right_is_background(
        _right.get<sanguis::client::draw2d::scene::world::sprite::is_background_role>());

    return left_is_background != right_is_background
               ? static_cast<int>(left_is_background) > static_cast<int>(right_is_background)
               : sge::sprite::compare::default_()(_left, _right);
  }
};

}

#endif
