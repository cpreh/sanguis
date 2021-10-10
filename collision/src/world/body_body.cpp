#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/length2.hpp>
#include <sanguis/collision/mass.hpp>
#include <sanguis/collision/optional_result_pair.hpp>
#include <sanguis/collision/result.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/impl/collides.hpp>
#include <sanguis/collision/impl/move_circle.hpp>
#include <sanguis/collision/impl/normalize_opt.hpp>
#include <sanguis/collision/impl/world/make_circle.hpp>
#include <sanguis/collision/world/body.hpp>
#include <sanguis/collision/world/body_body.hpp>
#include <fcppt/boost_units_value.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/dot.hpp>
#include <fcppt/math/vector/map.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe_multi.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/tuple/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/momentum.hpp>
#include <boost/units/systems/si/velocity.hpp>
#include <fcppt/config/external_end.hpp>

sanguis::collision::optional_result_pair sanguis::collision::world::body_body(
    sanguis::collision::world::body const &_body1,
    sanguis::collision::world::body const &_body2,
    sanguis::collision::duration const _duration)
{
  using impulse_type = boost::units::quantity<boost::units::si::momentum, sanguis::collision::unit>;

  using optional_impulse = fcppt::optional::object<impulse_type>;

  using normal_type = fcppt::math::vector::static_<sanguis::collision::unit, 2>;

  auto const make_impulse(
      [&_body1, &_body2, _duration](
          normal_type const &_normal,
          sanguis::collision::mass const &_mass1,
          sanguis::collision::mass const &_mass2) -> optional_impulse
      {
        sanguis::collision::unit const elasticity(fcppt::literal<sanguis::collision::unit>(0.9F));

        sanguis::collision::unit const one(fcppt::literal<sanguis::collision::unit>(1));

        auto const divisor(one / _mass1 + one / _mass2);

        sanguis::collision::impl::circle const circle1(
            sanguis::collision::impl::world::make_circle(_body1));

        sanguis::collision::impl::circle const circle2(
            sanguis::collision::impl::world::make_circle(_body2));

        return
				sanguis::collision::impl::collides(
					circle1,
					circle2
				)
				?
					optional_impulse(
						fcppt::literal<
							sanguis::collision::unit
						>(
							1.F
						)
						*
						boost::units::si::meter_per_second
						/
						divisor
					)
				:
					sanguis::collision::impl::collides(
						sanguis::collision::impl::move_circle(
							circle1,
							_body1.speed(),
							_duration
						),
						sanguis::collision::impl::move_circle(
							circle2,
							_body2.speed(),
							_duration
						)
					)
					?
						optional_impulse{
							(
								-(
									one
									+
									elasticity
								)
								*
								// TODO(philipp): Make a dot function that respects boost units
								fcppt::math::vector::dot(
									fcppt::math::vector::map(
										_body1.speed()
										-
										_body2.speed(),
										fcppt::boost_units_value{}
									),
									_normal
								)
								*
								boost::units::si::meter_per_second
							)
							/
							divisor
						}
					:
						optional_impulse{}
				;
      });

  return fcppt::optional::maybe_multi(
      [] { return sanguis::collision::optional_result_pair{}; },
      [make_impulse, &_body1, &_body2](
          sanguis::collision::mass const &_mass1, sanguis::collision::mass const &_mass2)
      {
        return fcppt::optional::bind(
            sanguis::collision::impl::normalize_opt(fcppt::math::vector::map(
                _body1.center().get() - _body2.center().get(), fcppt::boost_units_value{})),
            [make_impulse, _mass1, _mass2](normal_type const &_normal)
            {
              return fcppt::optional::map(
                  make_impulse(_normal, _mass1, _mass2),
                  [_mass1, _mass2, _normal](impulse_type const &_impulse)
                  {
                    auto const make_speed([_impulse, _normal](sanguis::collision::mass const &_mass)
                                          { return (_impulse / _mass) * _normal; });

                    return fcppt::tuple::make(
                        sanguis::collision::result(make_speed(_mass1)),
                        sanguis::collision::result(-make_speed(_mass2)));
                  });
            });
      },
      _body1.mass(),
      _body2.mass());
}
