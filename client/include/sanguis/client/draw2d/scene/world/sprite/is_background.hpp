#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_IS_BACKGROUND_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_IS_BACKGROUND_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/sprite/is_background_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/is_background_role.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/record/element.hpp>

namespace sanguis::client::draw2d::scene::world::sprite
{

struct is_background
{
  template <typename Choices>
  struct apply
  {
    using type = fcppt::mpl::list::object<fcppt::record::element<
        sanguis::client::draw2d::scene::world::sprite::is_background_role,
        bool>>;
  };
};

}

#endif
