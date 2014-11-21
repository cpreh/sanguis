#include <sanguis/client/slowed_duration.hpp>
#include <sanguis/client/draw2d/player_center.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/scene/world/base.hpp>
#include <sanguis/client/draw2d/scene/world/graveyard.hpp>
#include <sanguis/client/draw2d/sprite/client/system_fwd.hpp>
#include <sanguis/client/load/context_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>


sanguis::client::draw2d::scene::world::graveyard::graveyard(
	sanguis::client::load::context const &_load_context,
	sanguis::client::draw2d::sprite::client::system &_client_system,
	sge::viewport::manager &_viewport_manager
)
:
	sanguis::client::draw2d::scene::world::base(),
	light_{
		_load_context,
		_client_system,
		_viewport_manager
	}
{
}

sanguis::client::draw2d::scene::world::graveyard::~graveyard()
{
}

void
sanguis::client::draw2d::scene::world::graveyard::update(
	sanguis::client::slowed_duration
)
{
}

void
sanguis::client::draw2d::scene::world::graveyard::draw_after(
	sge::renderer::context::core &_render_context,
	sanguis::client::draw2d::player_center const _player_center,
	sanguis::client::draw2d::z_ordering const _z_ordering
)
{
	if(
		_z_ordering
		==
		sanguis::client::draw2d::z_ordering::player_upper
	)
		light_.draw(
			_render_context,
			_player_center
		);
}
