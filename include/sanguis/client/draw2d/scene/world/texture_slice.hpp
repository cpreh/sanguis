#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TEXTURE_SLICE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TEXTURE_SLICE_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/texture_slice_fwd.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>

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

class texture_slice
{
public:
	texture_slice(
		sge::renderer::first_vertex,
		sge::renderer::vertex_count,
		sge::texture::const_part_shared_ptr
	);

	sge::renderer::first_vertex const
	first_vertex() const;

	sge::renderer::vertex_count const
	vertex_count() const;

	sge::texture::const_part_shared_ptr const
	texture() const;
private:
	sge::renderer::first_vertex first_vertex_;

	sge::renderer::vertex_count vertex_count_;

	sge::texture::const_part_shared_ptr texture_;
};

}
}
}
}
}

#endif
