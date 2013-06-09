#include <sanguis/collision/adjust_speed.hpp>
#include <sanguis/collision/adjust_speed_one.hpp>
#include <sanguis/collision/center_fwd.hpp>
#include <sanguis/collision/radius_fwd.hpp>
#include <sanguis/collision/rect.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/vector2.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


sanguis::collision::speed const
sanguis::collision::adjust_speed(
	sanguis::creator::pos const _pos,
	sanguis::collision::speed const _speed,
	sanguis::collision::center const _center,
	sanguis::collision::radius const _radius
)
{
	sanguis::collision::speed new_speed(
		_speed
	);

	sanguis::collision::rect const rect(
		fcppt::math::vector::structure_cast<
			sanguis::collision::rect::vector
		>(
			_pos
		),
		fcppt::math::dim::fill<
			2
		>(
			static_cast<
				sanguis::collision::unit
			>(
				sanguis::creator::tile_size::value
			)
		)
	);

	new_speed =
		sanguis::collision::adjust_speed_one(
			_center,
			new_speed,
			_radius,
			rect,
			sanguis::collision::vector2(
				_speed.get().y(),
				-_speed.get().x()
			)
		);

	if(
		std::abs(
			new_speed.get().x()
		)
		+
		std::abs(
			new_speed.get().y()
		)
		<
		0.001f
	)
		return new_speed;

	new_speed =
		sanguis::collision::adjust_speed_one(
			_center,
			new_speed,
			_radius,
			rect,
			sanguis::collision::vector2(
				-_speed.get().y(),
				_speed.get().x()
			)
		);

	return
		new_speed;
}
