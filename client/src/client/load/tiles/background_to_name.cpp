#include <sanguis/creator/background_tile.hpp>
#include <sanguis/client/load/tiles/background_to_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/unreachable.hpp>


fcppt::string
sanguis::client::load::tiles::background_to_name(
	sanguis::creator::background_tile const _tile
)
{
	switch(
		_tile
	)
	{
	case sanguis::creator::background_tile::grass:
		return FCPPT_TEXT("grass");
	case sanguis::creator::background_tile::asphalt:
		return FCPPT_TEXT("asphalt");
	case sanguis::creator::background_tile::nothing:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}