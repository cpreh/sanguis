#include <sanguis/client/slowed_duration.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/scene/world/base.hpp>
#include <sanguis/client/draw2d/scene/world/graveyard.hpp>
#include <sanguis/client/draw2d/scene/world/render_parameters.hpp>
#include <sanguis/client/draw2d/sprite/client/system_ref.hpp>
#include <sanguis/client/load/context_cref.hpp>
#include <sge/viewport/manager_ref.hpp>

sanguis::client::draw2d::scene::world::graveyard::graveyard(
    sanguis::client::load::context_cref const _load_context,
    sanguis::client::draw2d::sprite::client::system_ref const _client_system,
    sge::viewport::manager_ref const _viewport_manager)
    : sanguis::client::draw2d::scene::world::base(),
      light_{_load_context, _client_system, _viewport_manager}
{
}

sanguis::client::draw2d::scene::world::graveyard::~graveyard() = default;

void sanguis::client::draw2d::scene::world::graveyard::update(sanguis::client::slowed_duration) {}

void sanguis::client::draw2d::scene::world::graveyard::draw_after(
    sanguis::client::draw2d::scene::world::render_parameters const &_parameters)
{
  light_.draw(_parameters.render_context());
}
