#include <sanguis/collision/length2.hpp>
#include <sanguis/collision/optional_result.hpp>
#include <sanguis/collision/result.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/impl/is_null.hpp>
#include <sanguis/collision/impl/world/simple/body.hpp>
#include <sanguis/collision/impl/world/simple/collides.hpp>
#include <sanguis/collision/impl/world/simple/push_near.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/boost_units_value.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/length.hpp>
#include <fcppt/math/vector/map.hpp>
#include <fcppt/math/vector/normalize.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/units/systems/si/velocity.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::collision::optional_result const
sanguis::collision::impl::world::simple::push_near(
	sanguis::collision::impl::world::simple::body const &_body1,
	sanguis::collision::impl::world::simple::body const &_body2
)
{
	if(
		&_body1
		==
		&_body2
		||
		!sanguis::collision::impl::world::simple::collides(
			_body1,
			_body2
		)
	)
		return
			sanguis::collision::optional_result();

	sanguis::collision::length2 const diff(
		_body1.center().get()
		-
		_body2.center().get()
	);

	return
		sanguis::collision::impl::is_null(
			fcppt::math::vector::length(
				fcppt::math::vector::map(
					diff,
					fcppt::boost_units_value{}
				)
			)
		)
		?
			sanguis::collision::optional_result()
		:
			sanguis::collision::optional_result(
				sanguis::collision::result(
					fcppt::math::vector::normalize(
						fcppt::math::vector::map(
							diff,
							fcppt::boost_units_value{}
						)
					)
					*
					(
						fcppt::literal<
							sanguis::collision::unit
						>(
							// TODO
							10
						)
						*
						boost::units::si::meter_per_second
					)
				)
			)
		;
}
