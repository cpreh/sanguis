#include <sanguis/client/draw2d/scene/world/batch.hpp>
#include <sanguis/client/draw2d/scene/world/texture_slice_vector.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/texture/const_optional_base_ref.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/vertex/buffer_shared_ptr.hpp>
#include <sge/renderer/vertex/scoped_buffer.hpp>
#include <sge/texture/part.hpp>


sanguis::client::draw2d::scene::world::batch::batch()
:
	vertex_buffer_(),
	texture_slices_()
{
}

sanguis::client::draw2d::scene::world::batch::batch(
	sge::renderer::vertex::buffer_shared_ptr const _vertex_buffer,
	sanguis::client::draw2d::scene::world::texture_slice_vector const &_texture_slices
)
:
	vertex_buffer_(
		_vertex_buffer
	),
	texture_slices_(
		_texture_slices
	)
{
}

void
sanguis::client::draw2d::scene::world::batch::draw(
	sge::renderer::context::core &_render_context
)
{
	if(
		this->empty()
	)
		return;

	sge::renderer::vertex::scoped_buffer const scoped_buffer(
		_render_context,
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
		_render_context.texture(
			sge::renderer::texture::const_optional_base_ref(
				it->texture()->texture()
			),
			sge::renderer::texture::stage(
				0u
			)
		);

		_render_context.render_nonindexed(
			it->first_vertex(),
			it->vertex_count(),
			sge::renderer::primitive_type::triangle_list
		);
	}
}

bool
sanguis::client::draw2d::scene::world::batch::empty() const
{
	return !vertex_buffer_;
}
