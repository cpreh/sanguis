#include <sanguis/creator/rect.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/tile_rect.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/null.hpp>

sanguis::creator::rect sanguis::creator::tile_rect(sanguis::creator::tile const /*_tile*/
)
{
  return sanguis::creator::rect(
      fcppt::math::vector::null<sanguis::creator::rect::vector>(),
      fcppt::math::dim::fill<sanguis::creator::rect::dim>(sanguis::creator::tile_size::value));
}
