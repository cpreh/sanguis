#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <fcppt/assert/unreachable.hpp>


bool
sanguis::creator::tile_is_solid(
	sanguis::creator::tile const _tile
)
{
	switch(
		_tile
	)
	{
	case sanguis::creator::tile::nothing:
	case sanguis::creator::tile::door:
		return false;
	case sanguis::creator::tile::concrete_wall:
		return true;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
