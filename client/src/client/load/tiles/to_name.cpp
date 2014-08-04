#include <sanguis/creator/tile.hpp>
#include <sanguis/client/load/tiles/to_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


fcppt::string
sanguis::client::load::tiles::to_name(
	sanguis::creator::tile const _tile
)
{
	switch(
		_tile
	)
	{
	case sanguis::creator::tile::concrete_wall:
		return
			FCPPT_TEXT("concrete_wall");
	case sanguis::creator::tile::stairs:
		return
			FCPPT_TEXT("stairs");
	case sanguis::creator::tile::space_door_closed_v:
		return
			FCPPT_TEXT("space_door_closed_v");
	case sanguis::creator::tile::space_door_open_v:
		return
			FCPPT_TEXT("space_door_open_v");
	case sanguis::creator::tile::space_door_closed_h:
		return
			FCPPT_TEXT("space_door_closed_h");
	case sanguis::creator::tile::space_door_open_h:
		return
			FCPPT_TEXT("space_door_open_h");
	case sanguis::creator::tile::grave1:
		return
			FCPPT_TEXT("grave1");
	case sanguis::creator::tile::grave2:
		return
			FCPPT_TEXT("grave2");
	case sanguis::creator::tile::grave3:
		return
			FCPPT_TEXT("grave3");
	case sanguis::creator::tile::grave4:
		return
			FCPPT_TEXT("grave4");
	case sanguis::creator::tile::grave5:
		return
			FCPPT_TEXT("grave5");
	case sanguis::creator::tile::hedge:
		return
			FCPPT_TEXT("hedge");
	case sanguis::creator::tile::spawner:
		return
			FCPPT_TEXT("spawner");
	case sanguis::creator::tile::nothing:
		return
			FCPPT_TEXT("nothing");
	}

	FCPPT_ASSERT_UNREACHABLE;
}
