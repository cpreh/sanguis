#include <sanguis/collision/optional_result.hpp>
#include <sanguis/collision/result.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/vector2.hpp>
#include <sanguis/collision/impl/world/simple/body.hpp>
#include <sanguis/collision/impl/world/simple/collides.hpp>
#include <sanguis/collision/impl/world/simple/push_near.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/length.hpp>
#include <fcppt/math/vector/normalize.hpp>


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

	sanguis::collision::vector2 const diff(
		_body1.center().get()
		-
		_body2.center().get()
	);

	if(
		fcppt::math::vector::length(
			diff
		)
		<=
		fcppt::literal<
			sanguis::collision::unit
		>(
			0.01f
		)
	)
		return
			sanguis::collision::optional_result();

	return
		sanguis::collision::optional_result(
			sanguis::collision::result(
				sanguis::collision::speed{
					fcppt::math::vector::normalize(
						diff
					)
					*
					fcppt::literal<
						sanguis::collision::unit
					>(
						// TODO
						10
					)
				}
			)
		);

}
