#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_STATE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_STATE_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/state_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/batch_grid.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/buffers.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/object.hpp>
#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/world_parameters_fwd.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/sprite/object_decl.hpp>
#include <sge/sprite/buffers/single_decl.hpp>
#include <sge/sprite/buffers/with_declaration_decl.hpp>
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
		sge::renderer::device &,
		load::resource::textures const &,
		sge::renderer::vertex_declaration const &,
		client::world_parameters const &
	);

	~state();

	void
	draw(
		sge::renderer::context::object &,
		draw2d::vector2 const &translation
	);
private:
	sge::renderer::device &renderer_;

	sge::renderer::vertex_declaration const &vertex_declaration_;

	typedef fcppt::scoped_ptr<
		world::batch_grid
	> batch_grid_scoped_ptr;

	batch_grid_scoped_ptr const batches_;

	world::sprite::buffers stencil_sprite_buffers_;

	world::sprite::object stencil_sprite_;
};

}
}
}
}
}

#endif
