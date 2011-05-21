#include "texture_slice.hpp"

sanguis::client::draw2d::scene::world::texture_slice::texture_slice(
	sge::renderer::first_vertex const _first_vertex,
	sge::renderer::vertex_count const _vertex_count,
	sge::texture::const_part_ptr const _texture
)
:
	first_vertex_(_first_vertex),
	vertex_count_(_vertex_count),
	texture_(_texture)
{
}

sge::renderer::first_vertex const
sanguis::client::draw2d::scene::world::texture_slice::first_vertex() const
{
	return first_vertex_;
}

sge::renderer::vertex_count const
sanguis::client::draw2d::scene::world::texture_slice::vertex_count()
{
	return vertex_count_;
}

sge::texture::const_part_ptr const
sanguis::client::draw2d::scene::world::texture_slice::texture() const
{
	return texture_;
}
