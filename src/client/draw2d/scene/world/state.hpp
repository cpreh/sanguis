#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_STATE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_STATE_HPP_INCLUDED

#include "state_fwd.hpp"
#include "batch_grid.hpp"
#include "../../vector2.hpp"
#include "../../../world_parameters_fwd.hpp"
#include "../../../../load/resource/textures_fwd.hpp"
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
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
		draw2d::vector2 const &translation
	);
private:
	sge::renderer::device &renderer_;

	typedef fcppt::scoped_ptr<
		world::batch_grid
	> batch_grid_scoped_ptr;

	batch_grid_scoped_ptr const batches_;
};

}
}
}
}
}

#endif
