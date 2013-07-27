#include <sanguis/creator/tile.hpp>
#include <sanguis/load/tiles/to_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


fcppt::string const
sanguis::load::tiles::to_name(
	sanguis::creator::tile const _tile
)
{
	switch(
		_tile
	)
	{
	case sanguis::creator::tile::concrete_wall:
		return FCPPT_TEXT("concrete_wall");
	case sanguis::creator::tile::door:
		return FCPPT_TEXT("door");
	case sanguis::creator::tile::nothing:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
