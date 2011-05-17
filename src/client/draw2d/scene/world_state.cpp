#include "world_state.hpp"

sanguis::client::draw2d::scene::world_state::world_state(
	sge::renderer::device &_renderer,
	client::world_parameters const &_parameters
)
:
	renderer_(_renderer)
{
}

sanguis::client::draw2d::scene::world_state::~world_state()
{
}

void
sanguis::client::draw2d::scene::world_state::draw(
	draw2d::vector2 const &_translation
)
{
}
