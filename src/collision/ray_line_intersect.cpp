#include <sanguis/collision/line_segment.hpp>
#include <sanguis/collision/ray_line_intersect.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/vector2.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


bool
sanguis::collision::ray_line_intersect(
	sanguis::collision::vector2 const _pos,
	sanguis::collision::speed const _dir,
	sanguis::collision::line_segment const _line
)
{
	sanguis::collision::unit const dot_perp(
		_dir.get().x() * _line.dir().y()
		-
		_dir.get().y() * _line.dir().x()
	);

	if(
		std::abs(
			dot_perp
		)
		< 0.001f
	)
		return false;

	sanguis::collision::vector2 const c(
		_line.pos()
		-
		_pos
	);

	sanguis::collision::unit const t(
		(
			c.x() * _line.dir().y()
			-
			c.y() * _line.dir().x()
		)
		/
		dot_perp
	);

	if(
		t < 0.f || t > 1.f
	)
		return false;

	sanguis::collision::unit const u(
		(
			c.x() * _dir.get().y()
			-
			c.y() * _dir.get().x()
		)
		/
		dot_perp
	);

	return
		u > 0.f;
}
