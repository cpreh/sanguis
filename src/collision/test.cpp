#include <sanguis/duration.hpp>
#include <sanguis/collision/adjust_speed.hpp>
#include <sanguis/collision/center.hpp>
#include <sanguis/collision/dim2.hpp>
#include <sanguis/collision/optional_result.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/result.hpp>
#include <sanguis/collision/scale.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/test.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/creator/difference_type.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/container/grid/clamp_signed_pos.hpp>
#include <fcppt/container/grid/make_pos_crange_start_end.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/ceil_div_signed.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


sanguis::collision::optional_result const
sanguis::collision::test(
	sanguis::collision::center const _center,
	sanguis::collision::radius const _radius,
	sanguis::collision::speed const _speed,
	sanguis::duration const _time,
	sanguis::creator::grid const &_grid
)
{
	sanguis::collision::center const new_center(
		_center.get()
		+
		_speed.get()
		*
		_time.count()
	);

	sanguis::collision::dim2 const scaled_size(
		fcppt::math::dim::fill<
			sanguis::collision::dim2::dim_wrapper::value
		>(
			_radius.get()
			/
			static_cast<
				sanguis::collision::unit
			>(
				sanguis::collision::scale()
			)
		)
	);

	sanguis::creator::pos const lower(
		fcppt::container::grid::clamp_signed_pos(
			fcppt::math::vector::structure_cast<
				sanguis::creator::signed_pos
			>(
				new_center.get()
				-
				scaled_size
				/
				fcppt::literal<
					sanguis::collision::unit
				>(
					2
				)
			)
			/
			static_cast<
				sanguis::creator::difference_type
			>(
				sanguis::creator::tile_size::value
			),
			_grid.size()
		)
	);

	sanguis::creator::pos const upper(
		fcppt::container::grid::clamp_signed_pos(
			fcppt::math::vector::ceil_div_signed(
				fcppt::math::vector::structure_cast<
					sanguis::creator::signed_pos
				>(
					new_center.get()
					+
					scaled_size
					/
					fcppt::literal<
						sanguis::collision::unit
					>(
						2
					)
				),
				static_cast<
					sanguis::creator::difference_type
				>(
					sanguis::creator::tile_size::value
				)
			),
			_grid.size()
		)
	);

	// TODO: Get rid of this and make a new function without speed!
	bool const speed_is_null(
		std::abs(
			_speed.get().x()
		)
		+
		std::abs(
			_speed.get().y()
		)
		<
		0.001f
	);

	bool changed(
		false
	);

	sanguis::collision::speed new_speed(
		_speed
	);

	for(
		auto const &entry
		:
		fcppt::container::grid::make_pos_crange_start_end(
			_grid,
			lower,
			upper
		)
	)
		if(
			sanguis::creator::tile_is_solid(
				entry.value()
			)
		)
		{
			changed = true;

			if(
				!speed_is_null
			)
				new_speed =
					sanguis::collision::adjust_speed(
						entry.pos()
						*
						sanguis::creator::tile_size::value,
						new_speed,
						_center,
						_radius
					);
		}

	return
		changed
		?
			sanguis::collision::optional_result(
				sanguis::collision::result(
					new_speed,
					_center
				)
			)
		:
			sanguis::collision::optional_result()
		;
}
