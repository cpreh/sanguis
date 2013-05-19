#include <sanguis/client/world_parameters_fwd.hpp>
#include <sanguis/client/draw2d/vector2_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/object.hpp>
#include <sanguis/client/draw2d/scene/world/state.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::client::draw2d::scene::world::object::object(
	sge::renderer::device::core &_renderer,
	sanguis::load::resource::textures const &_textures
)
:
	renderer_(
		_renderer
	),
	tiles_context_(
		_textures
	),
	state_()
{
}

sanguis::client::draw2d::scene::world::object::~object()
{
}

void
sanguis::client::draw2d::scene::world::object::draw(
	sge::renderer::context::core &_render_context,
	sanguis::client::draw2d::vector2 const &_translation
)
{
	if(
		state_
	)
		state_->draw(
			_render_context,
			_translation
		);
}

void
sanguis::client::draw2d::scene::world::object::change(
	sanguis::client::world_parameters const &_param
)
{
	state_.take(
		fcppt::make_unique_ptr<
			sanguis::client::draw2d::scene::world::state
		>(
			renderer_,
			tiles_context_,
			_param
		)
	);
}
