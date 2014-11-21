#include <sanguis/client/slowed_duration.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/scene/world/base.hpp>
#include <sanguis/client/draw2d/scene/world/graveyard.hpp>
#include <sanguis/client/draw2d/scene/world/render_parameters.hpp>
#include <sanguis/client/draw2d/sprite/client/system_fwd.hpp>
#include <sanguis/client/load/context_fwd.hpp>
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
	sanguis::client::draw2d::scene::world::render_parameters const &_parameters
)
{
	if(
		_parameters.z_ordering()
		==
		sanguis::client::draw2d::z_ordering::player_upper
	)
		light_.draw(
			_parameters.render_context(),
			_parameters.player_center()
		);
}
