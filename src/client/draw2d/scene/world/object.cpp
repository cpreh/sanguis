#include <sanguis/client/draw2d/scene/world/object.hpp>
#include <sanguis/client/draw2d/scene/world/state.hpp>
#include <sanguis/client/draw2d/scene/world/vf/format.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::client::draw2d::scene::world::object::object(
	sge::renderer::device::core &_renderer,
	sanguis::load::resource::textures const &_textures
)
:
	renderer_(
		_renderer
	),
	textures_(
		_textures
	),
	vertex_declaration_(
		renderer_.create_vertex_declaration(
			sge::renderer::vertex::declaration_parameters(
				sge::renderer::vf::dynamic::make_format<
					sanguis::client::draw2d::scene::world::vf::format
				>()
			)
		)
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
			scene::world::state
		>(
			renderer_,
			textures_,
			*vertex_declaration_,
			_param
		)
	);
}
