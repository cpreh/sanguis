#include <sanguis/client/draw2d/player_center.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/scene/world/render_parameters.hpp>
#include <sge/renderer/context/core_fwd.hpp>


sanguis::client::draw2d::scene::world::render_parameters::render_parameters(
	sge::renderer::context::core &_render_context,
	sanguis::client::draw2d::player_center const _player_center,
	sanguis::client::draw2d::z_ordering const _z_ordering
)
:
	render_context_(
		_render_context
	),
	player_center_{
		_player_center
	},
	z_ordering_{
		_z_ordering
	}
{
}

sge::renderer::context::core &
sanguis::client::draw2d::scene::world::render_parameters::render_context() const
{
	return
		render_context_;
}

sanguis::client::draw2d::player_center const
sanguis::client::draw2d::scene::world::render_parameters::player_center() const
{
	return
		player_center_;
}

sanguis::client::draw2d::z_ordering
sanguis::client::draw2d::scene::world::render_parameters::z_ordering() const
{
	return
		z_ordering_;
}
