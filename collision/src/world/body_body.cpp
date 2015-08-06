#include <sanguis/collision/length2.hpp>
#include <sanguis/collision/optional_result_pair.hpp>
#include <sanguis/collision/result.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/impl/normalize_opt.hpp>
#include <sanguis/collision/impl/world/collides.hpp>
#include <sanguis/collision/world/body.hpp>
#include <sanguis/collision/world/body_body.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/boost_units_value.hpp>
#include <fcppt/make_homogenous_pair.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/map.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/momentum.hpp>
#include <boost/units/systems/si/velocity.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::collision::optional_result_pair const
sanguis::collision::world::body_body(
	sanguis::collision::world::body const &_body1,
	sanguis::collision::world::body const &_body2
)
{
	return
		sanguis::collision::impl::world::collides(
			_body1,
			_body2
		)
		?
			fcppt::optional_bind_construct(
				sanguis::collision::impl::normalize_opt(
					fcppt::math::vector::map(
						_body1.center().get()
						-
						_body2.center().get()
						,
						fcppt::boost_units_value{}
					)
				),
				[
					&_body1,
					&_body2
				](
					fcppt::math::vector::static_<
						sanguis::collision::unit,
						2
					> const _normal
				)
				{
					sanguis::collision::unit const elasticity(
						fcppt::literal<
							sanguis::collision::unit
						>(
							0.7f
						)
					);

					sanguis::collision::unit const one(
						fcppt::literal<
							sanguis::collision::unit
						>(
							1
						)
					);

					sanguis::collision::speed const speed_diff(
						_body1.speed()
						-
						_body2.speed()
					);

					fcppt::math::vector::static_<
						boost::units::quantity<
							boost::units::si::momentum,
							sanguis::collision::unit
						>,
						2
					> const impulse(
						(
							-(
								one
								+
								elasticity
							)
							*
							speed_diff
							*
							_normal
						)
						/
						(
							_normal
							*
							_normal
							*
							(
								one
								/
								_body1.mass()
								+
								one
								/
								_body2.mass()
							)
						)
					);

					return
						fcppt::make_homogenous_pair(
							sanguis::collision::result(
								(
									impulse
									/
									_body1.mass()
								)
								*
								_normal
							),
							sanguis::collision::result(
								-(
									(
										impulse
										/
										_body2.mass()
									)
									*
									_normal
								)
							)
						);
				}
			)
		:
			sanguis::collision::optional_result_pair()
		;
}
