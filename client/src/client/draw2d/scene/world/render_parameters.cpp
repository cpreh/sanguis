#include <sanguis/client/draw2d/translation.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/scene/world/render_parameters.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/context/core_ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::scene::world::render_parameters::render_parameters(
	sge::renderer::context::core_ref const _render_context,
	sanguis::client::draw2d::translation _translation
)
:
	render_context_(
		_render_context
	),
	translation_{
		std::move(
			_translation
		)
	}
{
}

sge::renderer::context::core &
sanguis::client::draw2d::scene::world::render_parameters::render_context() const
{
	return
		render_context_.get();
}

sanguis::client::draw2d::translation
sanguis::client::draw2d::scene::world::render_parameters::translation() const
{
	return
		translation_;
}
