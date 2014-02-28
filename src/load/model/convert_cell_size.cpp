#include <sanguis/load/model/cell_size.hpp>
#include <sanguis/load/model/convert_cell_size.hpp>
#include <sanguis/model/cell_size.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sanguis::load::model::cell_size const
sanguis::load::model::convert_cell_size(
	sanguis::model::cell_size const &_cell_size
)
{
	return
		sanguis::load::model::cell_size(
			fcppt::math::dim::structure_cast<
				sanguis::load::model::cell_size::value_type
			>(
				_cell_size
			)
		);
}
