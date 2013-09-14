#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/aux_/serialization/grid.hpp>
#include <sanguis/creator/aux_/serialization/tile_grid.hpp>
#include <sge/parse/json/object.hpp>


sge::parse::json::object
sanguis::creator::aux_::serialization::grid(
	sanguis::creator::grid const &_grid
)
{
	return
		sanguis::creator::aux_::serialization::tile_grid(
			_grid
		);
}
