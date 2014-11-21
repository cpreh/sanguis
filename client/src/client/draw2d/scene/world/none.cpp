#include <sanguis/client/slowed_duration.hpp>
#include <sanguis/client/draw2d/player_center.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/scene/world/base.hpp>
#include <sanguis/client/draw2d/scene/world/none.hpp>
#include <sge/renderer/context/core_fwd.hpp>


sanguis::client::draw2d::scene::world::none::none()
:
	sanguis::client::draw2d::scene::world::base()
{
}

sanguis::client::draw2d::scene::world::none::~none()
{
}

void
sanguis::client::draw2d::scene::world::none::update(
	sanguis::client::slowed_duration
)
{
}

void
sanguis::client::draw2d::scene::world::none::draw_after(
	sge::renderer::context::core &,
	sanguis::client::draw2d::player_center,
	sanguis::client::draw2d::z_ordering
)
{
}
