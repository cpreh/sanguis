#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/aux_/deserialization/grid.hpp>
#include <sanguis/creator/aux_/deserialization/tile_grid.hpp>
#include <sge/parse/json/object.hpp>


sanguis::creator::grid
sanguis::creator::aux_::deserialization::grid(
	sge::parse::json::object const &_object
)
{
	return
		sanguis::creator::aux_::deserialization::tile_grid<
			sanguis::creator::grid
		>(
			_object
		);
}
