#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_BATCH_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_BATCH_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/batch_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/texture_slice_vector.hpp>
#include <sanguis/client/draw2d/scene/world/texture_slice.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/vertex_buffer_ptr.hpp>

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

class batch
{
public:
	batch();

	batch(
		sge::renderer::vertex_buffer_ptr,
		world::texture_slice_vector const &
	);

	void
	draw(
		sge::renderer::device &
	);
private:
	sge::renderer::vertex_buffer_ptr vertex_buffer_;

	world::texture_slice_vector texture_slices_;
};

}
}
}
}
}

#endif
