#include <sanguis/client/slowed_duration.hpp>
#include <sanguis/client/draw2d/scene/world/base.hpp>
#include <sanguis/client/draw2d/scene/world/none.hpp>
#include <sanguis/client/draw2d/scene/world/render_parameters.hpp>


sanguis::client::draw2d::scene::world::none::none()
:
	sanguis::client::draw2d::scene::world::base()
{
}

sanguis::client::draw2d::scene::world::none::~none()
= default;

void
sanguis::client::draw2d::scene::world::none::update(
	sanguis::client::slowed_duration
)
{
}

void
sanguis::client::draw2d::scene::world::none::draw_after(
	sanguis::client::draw2d::scene::world::render_parameters const &
)
{
}
