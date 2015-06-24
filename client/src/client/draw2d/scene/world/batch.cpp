#include <sanguis/client/draw2d/scene/world/batch.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/range.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/state.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/state_choices.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/sprite/render/parameters.hpp>
#include <sge/sprite/render/range_with_options.hpp>
#include <sge/sprite/state/options.hpp>
#include <sge/sprite/state/vertex_options.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::scene::world::batch::batch()
:
	range_()
{
}

sanguis::client::draw2d::scene::world::batch::batch(
	sanguis::client::draw2d::scene::world::sprite::range &&_range
)
:
	range_(
		std::move(
			_range
		)
	)
{
}

void
sanguis::client::draw2d::scene::world::batch::draw(
	sge::renderer::context::core &_render_context,
	sge::renderer::vertex::declaration const &_vertex_declaration,
	sanguis::client::draw2d::scene::world::sprite::state &_state
) const
{
	sge::sprite::render::range_with_options(
		sge::sprite::render::parameters<
			sanguis::client::draw2d::scene::world::sprite::state_choices
		>(
			_render_context,
			_vertex_declaration
		),
		range_,
		_state,
		sge::sprite::state::options<
			sanguis::client::draw2d::scene::world::sprite::state_choices
		>(
			sge::sprite::state::vertex_options::buffer
		)
	);
}
