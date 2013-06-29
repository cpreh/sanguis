#include <sanguis/collision/center.hpp>
#include <sanguis/collision/make_tangent_pos.hpp>
#include <sanguis/collision/pos.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/vector2.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/normalize.hpp>


sanguis::collision::pos const
sanguis::collision::make_tangent_pos(
	sanguis::collision::center const _center,
	sanguis::collision::radius const _radius,
	sanguis::collision::vector2 const _perp
)
{
	return
		sanguis::collision::pos(
			_center.get()
			+
			fcppt::math::vector::normalize(
				_perp
			)
			*
			_radius.get()
		);
}
