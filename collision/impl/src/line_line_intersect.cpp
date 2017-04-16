#include <sanguis/collision/length2.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/impl/cross2.hpp>
#include <sanguis/collision/impl/is_null.hpp>
#include <sanguis/collision/impl/line_line_intersect.hpp>
#include <sanguis/collision/impl/line_segment.hpp>
#include <fcppt/boost_units_value.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/map.hpp>


bool
sanguis::collision::impl::line_line_intersect(
	sanguis::collision::impl::line_segment const _line1,
	sanguis::collision::impl::line_segment const _line2
)
{
	sanguis::collision::unit const dot_perp(
		sanguis::collision::impl::cross2(
			fcppt::math::vector::map(
				_line1.dir().get(),
				fcppt::boost_units_value{}
			),
			fcppt::math::vector::map(
				_line2.dir().get(),
				fcppt::boost_units_value{}
			)
		)
	);

	if(
		sanguis::collision::impl::is_null(
			dot_perp
		)
	)
		return
			false;

	sanguis::collision::length2 const c(
		_line2.pos().get()
		-
		_line1.pos().get()
	);

	sanguis::collision::unit const t(
		sanguis::collision::impl::cross2(
			fcppt::math::vector::map(
				c,
				fcppt::boost_units_value{}
			),
			fcppt::math::vector::map(
				_line2.dir().get(),
				fcppt::boost_units_value{}
			)
		)
		/
		dot_perp
	);

	sanguis::collision::unit const one(
		fcppt::literal<
			sanguis::collision::unit
		>(
			1
		)
	);

	sanguis::collision::unit const zero(
		fcppt::literal<
			sanguis::collision::unit
		>(
			0
		)
	);

	if(
		t < zero || t > one
	)
		return
			false;

	sanguis::collision::unit const u(
		sanguis::collision::impl::cross2(
			fcppt::math::vector::map(
				c,
				fcppt::boost_units_value{}
			),
			fcppt::math::vector::map(
				_line1.dir().get(),
				fcppt::boost_units_value{}
			)
		)
		/
		dot_perp
	);

	return
		u >= zero && u <= one;
}
