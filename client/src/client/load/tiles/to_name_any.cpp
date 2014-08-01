#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/client/load/tiles/background_to_name.hpp>
#include <sanguis/client/load/tiles/to_name.hpp>
#include <sanguis/client/load/tiles/to_name_any.hpp>
#include <fcppt/string.hpp>


fcppt::string
sanguis::client::load::tiles::to_name_any(
	sanguis::creator::tile const _tile
)
{
	return
		sanguis::client::load::tiles::to_name(
			_tile
		);
}

fcppt::string
sanguis::client::load::tiles::to_name_any(
	sanguis::creator::background_tile const _tile
)
{
	return
		sanguis::client::load::tiles::background_to_name(
			_tile
		);
}
