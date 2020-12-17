#include <sanguis/model/animation_index.hpp>
#include <sanguis/model/cell_area.hpp>
#include <sanguis/model/cell_area_from_index.hpp>
#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/cell_size_unit.hpp>
#include <sanguis/model/dim.hpp>
#include <sanguis/model/image_size.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sanguis::model::cell_area
sanguis::model::cell_area_from_index(
	sanguis::model::image_size const &_image_size,
	sanguis::model::cell_size const &_cell_size,
	sanguis::model::animation_index const _index
)
{
	if(
		_image_size.get().w()
		==
		_cell_size.get().w()
	)
	{
		FCPPT_ASSERT_ERROR(
			_index == 0U
		);

		return
			sanguis::model::cell_area(
				fcppt::math::vector::null<
					sanguis::model::cell_area::vector
				>(),
				_cell_size.get()
			);
	}

	sanguis::model::dim const cell_size_edited(
		_cell_size.get()
		+
		fcppt::math::dim::fill<
			sanguis::model::dim
		>(
			1U
		)
	);

	sanguis::model::cell_size_unit const cells_per_row(
		std::max(
			_image_size.get().w()
			/
			cell_size_edited.w()
			,
			fcppt::literal<
				sanguis::model::cell_size_unit
			>(
				1U
			)
		)
	);

	return
		sanguis::model::cell_area(
			sanguis::model::cell_area::vector(
				_index
				%
				cells_per_row
				,
				_index
				/
				cells_per_row
			)
			*
			cell_size_edited
			,
			_cell_size.get()
		);
}
