#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_RENDER_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_RENDER_PARAMETERS_HPP_INCLUDED

#include <sanguis/client/draw2d/translation.hpp>
#include <sanguis/client/draw2d/scene/world/render_parameters_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/context/core_ref.hpp>

namespace sanguis::client::draw2d::scene::world
{

class render_parameters
{
public:
  render_parameters(sge::renderer::context::core_ref, sanguis::client::draw2d::translation);

  [[nodiscard]] sge::renderer::context::core &render_context() const;

  [[nodiscard]] sanguis::client::draw2d::translation translation() const;

private:
  sge::renderer::context::core_ref render_context_;

  sanguis::client::draw2d::translation translation_;
};

}

#endif
