#include <sanguis/collision/center.hpp>
#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/impl/adjust_speed.hpp>
#include <sanguis/collision/impl/dir.hpp>
#include <sanguis/collision/impl/grid_to_meter.hpp>
#include <sanguis/collision/impl/line_segment.hpp>
#include <sanguis/collision/impl/move.hpp>
#include <sanguis/collision/impl/optional_speed.hpp>
#include <sanguis/collision/impl/pos.hpp>
#include <sanguis/collision/impl/rect.hpp>
#include <sanguis/collision/impl/test_tile.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/rect.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/creator/tile_rect.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_literal_boost_units.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/math/box/intersects.hpp>
#include <fcppt/math/box/stretch_absolute.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/dim/map.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/fill.hpp>
#include <fcppt/math/vector/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/units/systems/si/length.hpp>
#include <fcppt/config/external_end.hpp>

sanguis::collision::impl::optional_speed sanguis::collision::impl::test_tile(
    sanguis::collision::center const &_center,
    sanguis::collision::radius const &_radius,
    sanguis::collision::duration const _time,
    sanguis::collision::speed const &_speed,
    sanguis::creator::pos const &_pos,
    sanguis::creator::tile const _tile)
{
  if (!sanguis::creator::tile_is_solid(_tile))
  {
    return sanguis::collision::impl::optional_speed();
  }

  sanguis::collision::center const new_center(
      sanguis::collision::impl::move(_center, _speed, _time));

  sanguis::collision::impl::rect const rect(fcppt::math::box::stretch_absolute(
      sanguis::collision::impl::rect(
          new_center.get(),
          fcppt::math::dim::fill<sanguis::collision::impl::rect::dim>(
              fcppt::literal<sanguis::collision::unit>(0) * boost::units::si::meter)),
      fcppt::math::vector::fill<sanguis::collision::impl::rect::vector>(_radius.get())));

  sanguis::creator::rect const tile_rect(sanguis::creator::tile_rect(_tile));

  sanguis::collision::impl::rect const entry_rect(
      fcppt::math::vector::map(tile_rect.pos(), &sanguis::collision::impl::grid_to_meter) +
          fcppt::math::vector::map(
              _pos * sanguis::creator::tile_size::value, &sanguis::collision::impl::grid_to_meter),
      fcppt::math::dim::map(tile_rect.size(), &sanguis::collision::impl::grid_to_meter));

  return fcppt::math::box::intersects(rect, entry_rect)
             ? sanguis::collision::impl::optional_speed(sanguis::collision::impl::adjust_speed(
                   sanguis::collision::impl::line_segment(
                       sanguis::collision::impl::pos(_center.get()),
                       sanguis::collision::impl::dir(new_center.get() - _center.get())),
                   _radius,
                   entry_rect,
                   _speed))
             : sanguis::collision::impl::optional_speed();
}
