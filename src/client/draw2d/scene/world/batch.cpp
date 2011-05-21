#include "batch.hpp"
#include <sge/renderer/device.hpp>
#include <sge/renderer/nonindexed_primitive_type.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/stage_type.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/texture/part.hpp>

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

void
sanguis::client::draw2d::scene::world::batch::render(
	sge::renderer::device &_renderer
)
{
	sge::renderer::scoped_vertex_buffer const scoped_buffer(
		_renderer,
		*vertex_buffer_
	);

	for(
		world::texture_slice_vector::const_iterator it(
			texture_slices_.begin()
		);
		it != texture_slices_.end();
		++it
	)
	{
		_renderer.texture(
			it->texture()->texture().get(),
			sge::renderer::stage_type(
				0u
			)
		);

		_renderer.render(
			it->first_vertex(),
			it->vertex_count(),
			sge::renderer::nonindexed_primitive_type::triangle
		);
	}
}
