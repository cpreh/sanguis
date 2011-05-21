#include "batch.hpp"

sanguis::client::draw2d::scene::world::batch::batch()
{
}

sanguis::client::draw2d::scene::world::batch::batch(
	sge::renderer::vertex_buffer_ptr const _vertex_buffer,
	world::texture_slice_vector const &_texture_slices
)
:
	vertex_buffer_(_vertex_buffer),
	texture_slices_(_texture_slices)
{
}
