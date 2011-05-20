#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_BATCH_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_BATCH_HPP_INCLUDED

#include "batch_fwd.hpp"
#include "texture_slice_vector.hpp"
#include "texture_slice.hpp"
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
		sge::renderer::device &,
		sge::renderer::vertex_buffer_ptr,
		world::texture_slice_vector const &
	);
private:
	sge::renderer::device *device_;

	sge::renderer::vertex_buffer_ptr vertex_buffer_;	

	world::texture_slice_vector texture_slices_;
};

}
}
}
}
}

#endif
