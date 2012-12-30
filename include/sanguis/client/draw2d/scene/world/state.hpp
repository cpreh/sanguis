#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_STATE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_STATE_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/state_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/batch_grid.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/buffers.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/object.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/state.hpp>
#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/world_parameters_fwd.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/object_scoped_ptr.hpp>
#include <sge/sprite/object_decl.hpp>
#include <sge/sprite/buffers/single_decl.hpp>
#include <sge/sprite/buffers/with_declaration_decl.hpp>
#include <sge/sprite/state/object_decl.hpp>
#include <fcppt/container/grid/object_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>


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
		sge::renderer::vertex::declaration const &,
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

	sge::renderer::vertex::declaration const &vertex_declaration_;

	typedef fcppt::scoped_ptr<
		sanguis::client::draw2d::scene::world::batch_grid
	> batch_grid_scoped_ptr;

	batch_grid_scoped_ptr const batches_;

	sanguis::client::draw2d::scene::world::sprite::buffers stencil_sprite_buffers_;

	sanguis::client::draw2d::scene::world::sprite::state stencil_sprite_states_;

	sanguis::client::draw2d::scene::world::sprite::object stencil_sprite_;

	sge::renderer::state::core::depth_stencil::object_scoped_ptr const batch_stencil_state_;

	sge::renderer::state::core::depth_stencil::object_scoped_ptr const mask_stencil_state_;
};

}
}
}
}
}

#endif
