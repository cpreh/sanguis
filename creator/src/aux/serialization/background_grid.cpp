#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/aux/serialization/background_grid.hpp>
#include <sanguis/creator/aux/serialization/tile_grid.hpp>
#include <sge/parse/json/object.hpp>


sge::parse::json::object
sanguis::creator::aux::serialization::background_grid(
	sanguis::creator::background_grid const &_grid
)
{
	return
		sanguis::creator::aux::serialization::tile_grid(
			_grid
		);
}
