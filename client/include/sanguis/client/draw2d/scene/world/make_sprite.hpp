#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_MAKE_SPRITE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_MAKE_SPRITE_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/optional_object.hpp>
#include <sanguis/client/load/tiles/context_ref.hpp>
#include <sanguis/tiles/cell_fwd.hpp>


namespace sanguis::client::draw2d::scene::world
{

sanguis::client::draw2d::scene::world::sprite::optional_object
make_sprite(
	sanguis::random_generator &, // NOLINT(google-runtime-references)
	sanguis::client::draw::debug,
	sanguis::client::load::tiles::context_ref,
	sanguis::tiles::cell const &
);

}

#endif
