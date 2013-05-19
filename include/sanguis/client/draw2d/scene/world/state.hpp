#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_STATE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_STATE_HPP_INCLUDED

#include <sanguis/client/world_parameters_fwd.hpp>
#include <sanguis/client/draw2d/vector2_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/batch_grid.hpp>
#include <sanguis/client/draw2d/scene/world/state_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/buffers.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/state.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{
namespace world
{

class state
{
	FCPPT_NONCOPYABLE(
		state
	);
public:
	state();

	state(
		sge::renderer::device::core &,
		sanguis::load::resource::textures const &,
		sanguis::client::world_parameters const &
	);

	~state();

	void
	draw(
		sge::renderer::context::core &,
		sanguis::client::draw2d::vector2 const &translation
	);
private:
	sge::renderer::device::core &renderer_;

	sanguis::client::draw2d::scene::world::sprite::buffers sprite_buffers_;

	sanguis::client::draw2d::scene::world::sprite::state sprite_state_;

	sanguis::client::draw2d::scene::world::batch_grid const batches_;
};

}
}
}
}
}

#endif
