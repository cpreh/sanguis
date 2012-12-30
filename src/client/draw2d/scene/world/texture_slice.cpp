#include <sanguis/client/draw2d/scene/world/texture_slice.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>


sanguis::client::draw2d::scene::world::texture_slice::texture_slice(
	sge::renderer::vertex::first const _first_vertex,
	sge::renderer::vertex::count const _vertex_count,
	sge::texture::const_part_shared_ptr const _texture
)
:
	first_vertex_(
		_first_vertex
	),
	vertex_count_(
		_vertex_count
	),
	texture_(
		_texture
	)
{
}

sge::renderer::vertex::first const
sanguis::client::draw2d::scene::world::texture_slice::first_vertex() const
{
	return first_vertex_;
}

sge::renderer::vertex::count const
sanguis::client::draw2d::scene::world::texture_slice::vertex_count() const
{
	return vertex_count_;
}

sge::texture::const_part_shared_ptr const
sanguis::client::draw2d::scene::world::texture_slice::texture() const
{
	return texture_;
}
