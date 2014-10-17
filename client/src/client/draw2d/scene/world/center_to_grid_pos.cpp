#include <sanguis/client/draw2d/scene/world/center_to_grid_pos.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/creator/center_to_grid_pos.hpp>
#include <sanguis/creator/pos.hpp>


sanguis::creator::pos
sanguis::client::draw2d::scene::world::center_to_grid_pos(
	sanguis::client::draw2d::sprite::center const _center
)
{
	return
		sanguis::creator::center_to_grid_pos(
			_center.get()
		);
}
