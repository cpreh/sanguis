#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/aux/serialization/grid.hpp>
#include <sanguis/creator/aux/serialization/tile_grid.hpp>
#include <sge/parse/json/object.hpp>


sge::parse::json::object
sanguis::creator::aux::serialization::grid(
	sanguis::creator::grid const &_grid
)
{
	return
		sanguis::creator::aux::serialization::tile_grid(
			_grid
		);
}
