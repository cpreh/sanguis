#include "world.hpp"
#include "world_state.hpp"
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sanguis::client::draw2d::scene::world::world(
	sge::renderer::device &_renderer
)
:
	renderer_(_renderer),
	world_state_()
{
}

sanguis::client::draw2d::scene::world::~world()
{
}

void
sanguis::client::draw2d::scene::world::draw(
	draw2d::vector2 const &_translation
)
{
	if(
		world_state_
	)
		world_state_->draw(
			_translation
		);
}

void
sanguis::client::draw2d::scene::world::change(
	client::world_parameters const &_param
)
{
	world_state_.take(
		fcppt::make_unique_ptr<
			scene::world_state
		>(
			fcppt::ref(
				renderer_
			),
			_param	
		)
	);
}
