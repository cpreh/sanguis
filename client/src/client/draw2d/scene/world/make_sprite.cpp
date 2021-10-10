#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/draw2d/scene/world/make_sprite.hpp>
#include <sanguis/client/draw2d/scene/world/make_texture.hpp>
#include <sanguis/client/draw2d/scene/world/tile_size.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/dim.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/is_background_role.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/object.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/optional_object.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/vector.hpp>
#include <sanguis/client/load/tiles/context_ref.hpp>
#include <sanguis/tiles/cell.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional/map.hpp>

sanguis::client::draw2d::scene::world::sprite::optional_object
sanguis::client::draw2d::scene::world::make_sprite(
    sanguis::random_generator &_random_generator,
    sanguis::client::draw::debug const _debug,
    sanguis::client::load::tiles::context_ref const _tiles,
    sanguis::tiles::cell const &_cell)
{
  return fcppt::optional::map(
      sanguis::client::draw2d::scene::world::make_texture(
          _random_generator, _debug, _tiles, _cell.path().get(), _cell.content()),
      [&_cell](fcppt::reference<sge::texture::part const> const _texture)
      {
        return sanguis::client::draw2d::scene::world::sprite::object(
            sge::sprite::roles::pos{} = fcppt::math::vector::structure_cast<
                sanguis::client::draw2d::scene::world::sprite::vector,
                fcppt::cast::size_fun>(_cell.pos()),
            sge::sprite::roles::size{} =
                fcppt::math::dim::fill<sanguis::client::draw2d::scene::world::sprite::dim>(
                    sanguis::client::draw2d::scene::world::tile_size::value),
            sge::sprite::roles::texture0{} =
                sanguis::client::draw2d::scene::world::sprite::object::texture_type{_texture.get()},
            sanguis::client::draw2d::scene::world::sprite::is_background_role{} =
                _cell.is_background().get());
      });
}
