#include <sanguis/load/model/calc_rect.hpp>
#include <sanguis/load/model/cell_size.hpp>
#include <sanguis/model/animation_index.hpp>
#include <sanguis/model/cell_area.hpp>
#include <sanguis/model/cell_area_from_index.hpp>
#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/image_size.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sge::renderer::lock_rect const
sanguis::load::model::calc_rect(
	sge::renderer::lock_rect const &_area,
	sanguis::load::model::cell_size const _cell_size,
	sge::renderer::size_type const _index
)
{
	sanguis::model::cell_area const result(
		sanguis::model::cell_area_from_index(
			sanguis::model::image_size(
				fcppt::math::dim::structure_cast<
					sanguis::model::image_size::value_type
				>(
					_area.size()
				)
			),
			sanguis::model::cell_size(
				fcppt::math::dim::structure_cast<
					sanguis::model::cell_size::value_type
				>(
					_cell_size.get()
				)
			),
			fcppt::cast::size<
				sanguis::model::animation_index
			>(
				_index
			)
		)
	);

	return
		sge::renderer::lock_rect(
			fcppt::math::vector::structure_cast<
				sge::renderer::lock_rect::vector
			>(
				result.pos()
			)
			+
			_area.pos(),
			fcppt::math::dim::structure_cast<
				sge::renderer::lock_rect::dim
			>(
				result.size()
			)
		);
}
