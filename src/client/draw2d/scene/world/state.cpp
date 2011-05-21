#include "state.hpp"
#include "batch.hpp"
#include "batch_grid.hpp"
#include "generate_batches.hpp"
#include "../../../world_parameters.hpp"
#include <fcppt/container/grid/object_impl.hpp>

sanguis::client::draw2d::scene::world::state::state(
	sge::renderer::device &_renderer,
	load::resource::textures const &_textures,
	sge::renderer::vertex_declaration const &_vertex_declaration,
	client::world_parameters const &_parameters
)
:
	renderer_(_renderer),
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
	
}
