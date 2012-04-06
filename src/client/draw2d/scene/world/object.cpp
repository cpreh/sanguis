#include <sanguis/client/draw2d/scene/world/object.hpp>
#include <sanguis/client/draw2d/scene/world/state.hpp>
#include <sanguis/client/draw2d/scene/world/vf/format.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/vertex_declaration.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sanguis::client::draw2d::scene::world::object::object(
	sge::renderer::device &_renderer,
	load::resource::textures const &_textures
)
:
	renderer_(_renderer),
	textures_(_textures),
	vertex_declaration_(
		renderer_.create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<
				world::vf::format
			>()
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
			fcppt::cref(
				textures_
			),
			fcppt::cref(
				*vertex_declaration_
			),
			fcppt::cref(
				_param
			)
		)
	);
}
