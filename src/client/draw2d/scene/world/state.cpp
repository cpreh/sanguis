#include "state.hpp"
#include "batch.hpp"
#include "batch_grid.hpp"
#include "generate_batches.hpp"
#include "../../../world_parameters.hpp"
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <fcppt/container/grid/object_impl.hpp>

sanguis::client::draw2d::scene::world::state::state(
	sge::renderer::device &_renderer,
	load::resource::textures const &_textures,
	sge::renderer::vertex_declaration const &_vertex_declaration,
	client::world_parameters const &_parameters
)
:
	renderer_(_renderer),
	vertex_declaration_(_vertex_declaration),
	batches_(
		world::generate_batches(
			_renderer,
			_vertex_declaration,
			_parameters.top_parameters(),
			_textures
		)
	)
{
}

sanguis::client::draw2d::scene::world::state::~state()
{
}

void
sanguis::client::draw2d::scene::world::state::draw(
	draw2d::vector2 const &_translation
)
{
	sge::renderer::scoped_vertex_declaration const scoped_decl(
		renderer_,
		vertex_declaration_
	);

	// TODO: draw batches with the stencil buffer
	// Also check which are not visible
	for(
		batch_grid::iterator batch_it(
			batches_->begin()
		);
		batch_it != batches_->end();
		++batch_it
	)
		batch_it->draw(
			renderer_
		);
}
