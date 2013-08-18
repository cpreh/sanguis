#include <sanguis/load/model/calc_rect.hpp>
#include <sanguis/load/model/cell_size.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sge::renderer::lock_rect const
sanguis::load::model::calc_rect(
	sge::renderer::lock_rect const &_area,
	sanguis::load::model::cell_size const _cell_size,
	sge::renderer::size_type const _index
)
{
	if(
		_area.size().w() == _cell_size.get().w()
	)
	{
		FCPPT_ASSERT_ERROR(
			_index == 0u
		);

		return
			sge::renderer::lock_rect(
				sge::renderer::lock_rect::vector::null(),
				_cell_size.get()
			);
	}

	sge::renderer::dim2 const cell_size_edited(
		_cell_size.get()
		+
		fcppt::math::dim::fill<
			sge::renderer::dim2::dim_wrapper::value
		>(
			1u
		)
	);

	sge::renderer::size_type const cells_per_row(
		std::max(
			_area.size().w()
			/
			cell_size_edited.w()
			,
			fcppt::literal<
				sge::renderer::size_type
			>(
				1u
			)
		)
	);

	return
		sge::renderer::lock_rect(
			sge::renderer::lock_rect::vector(
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
			+
			_area.pos()
			,
			_cell_size.get()
		);
}
