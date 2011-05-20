#include "object.hpp"
#include "state.hpp"
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sanguis::client::draw2d::scene::world::object::object(
	sge::renderer::device &_renderer,
	load::resource::textures const &_textures
)
:
	renderer_(_renderer),
	textures_(_textures),
	state_()
{
}

sanguis::client::draw2d::scene::world::object::~object()
{
}

void
sanguis::client::draw2d::scene::world::object::draw(
	draw2d::vector2 const &_translation
)
{
	if(
		state_
	)
		state_->draw(
			_translation
		);
}

void
sanguis::client::draw2d::scene::world::object::change(
	client::world_parameters const &_param
)
{
	state_.take(
		fcppt::make_unique_ptr<
			scene::world::state
		>(
			fcppt::ref(
				renderer_
			),
			_param,
			textures_
		)
	);
}
