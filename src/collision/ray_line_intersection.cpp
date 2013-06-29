#include <sanguis/collision/dir.hpp>
#include <sanguis/collision/is_null.hpp>
#include <sanguis/collision/line_segment.hpp>
#include <sanguis/collision/optional_unit.hpp>
#include <sanguis/collision/pos.hpp>
#include <sanguis/collision/ray_line_intersection.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/vector2.hpp>
#include <fcppt/math/vector/arithmetic.hpp>


sanguis::collision::optional_unit const
sanguis::collision::ray_line_intersection(
	sanguis::collision::pos const _pos,
	sanguis::collision::dir const _dir,
	sanguis::collision::line_segment const _line
)
{
	sanguis::collision::unit const dot_perp(
		_dir.get().x() * _line.dir().get().y()
		-
		_dir.get().y() * _line.dir().get().x()
	);

	if(
		sanguis::collision::is_null(
			dot_perp
		)
	)
		return
			sanguis::collision::optional_unit();

	sanguis::collision::vector2 const c(
		_line.pos().get()
		-
		_pos.get()
	);

	sanguis::collision::unit const t(
		(
			c.x() * _line.dir().get().y()
			-
			c.y() * _line.dir().get().x()
		)
		/
		dot_perp
	);

	if(
		t < 0.f || t > 1.f
	)
		return
			sanguis::collision::optional_unit();

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
		u < 0.f
		?
			sanguis::collision::optional_unit()
		:
			sanguis::collision::optional_unit(
				u
			)
		;
}
