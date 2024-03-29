#include <sanguis/collision/exception.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/velocity.hpp>
#include <sanguis/collision/impl/adjust_speed.hpp>
#include <sanguis/collision/impl/intersection.hpp>
#include <sanguis/collision/impl/is_null.hpp>
#include <sanguis/collision/impl/line_segment.hpp>
#include <sanguis/collision/impl/rect.hpp>
#include <sanguis/collision/impl/rect_line_intersection.hpp>
#include <fcppt/const.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_literal_boost_units.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/text.hpp>
#include <fcppt/math/box/stretch_absolute.hpp>
#include <fcppt/math/vector/fill.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/units/systems/si/velocity.hpp>
#include <fcppt/config/external_end.hpp>

sanguis::collision::speed sanguis::collision::impl::adjust_speed(
    sanguis::collision::impl::line_segment const &_movement,
    sanguis::collision::radius const &_radius,
    sanguis::collision::impl::rect const &_obstacle,
    sanguis::collision::speed const &_old_speed)
{
  return fcppt::optional::maybe(
      sanguis::collision::impl::rect_line_intersection(
          fcppt::math::box::stretch_absolute(
              _obstacle,
              fcppt::math::vector::fill<sanguis::collision::impl::rect::vector>(_radius.get())),
          _movement),
      fcppt::const_(_old_speed),
      [_old_speed](sanguis::collision::impl::intersection const &_intersection)
      {
        bool const vertical(
            sanguis::collision::impl::is_null(_intersection.dir().get().x().value()));

        bool const horizontal(
            sanguis::collision::impl::is_null(_intersection.dir().get().y().value()));

        if (vertical == horizontal)
        {
          throw sanguis::collision::exception{
              FCPPT_TEXT("adjust_speed: vertical and horizontal set!")};
        }

        sanguis::collision::velocity const zero{
            fcppt::literal<sanguis::collision::unit>(0) * boost::units::si::meter_per_second};

        return vertical ? sanguis::collision::speed(zero, _old_speed.y())
                        : sanguis::collision::speed(_old_speed.x(), zero);
      });
}
