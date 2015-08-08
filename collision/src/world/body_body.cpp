#include <sanguis/collision/length2.hpp>
#include <sanguis/collision/mass.hpp>
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
#include <fcppt/maybe_multi.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/dot.hpp>
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
		fcppt::maybe_multi(
			[]{
				return
					sanguis::collision::optional_result_pair{};
			},
			[
				&_body1,
				&_body2
			](
				sanguis::collision::mass const _mass1,
				sanguis::collision::mass const _mass2
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
								&_body2,
								_mass1,
								_mass2
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
										0.9f
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

								boost::units::quantity<
									boost::units::si::momentum,
									sanguis::collision::unit
								> const impulse(
									(
										-(
											one
											+
											elasticity
										)
										*
										// TODO: Make a dot function that respects boost units
										fcppt::math::vector::dot(
											fcppt::math::vector::map(
												speed_diff,
												fcppt::boost_units_value{}
											),
											_normal
										)
										*
										boost::units::si::meter_per_second
									)
									/
									(
										one
										/
										_mass1
										+
										one
										/
										_mass2
									)
								);

								auto const make_speed(
									[
										impulse,
										_normal
									](
										sanguis::collision::mass const _mass
									)
									{
										return
											(
												impulse
												/
												_mass
											)
											*
											_normal;
									}
								);

								return
									fcppt::make_homogenous_pair(
										sanguis::collision::result(
											make_speed(
												_mass1
											)
										),
										sanguis::collision::result(
											-make_speed(
												_mass2
											)
										)
									);
							}
						)
					:
						sanguis::collision::optional_result_pair()
					;
			},
			_body1.mass(),
			_body2.mass()
		);
}
