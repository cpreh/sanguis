#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_RENDER_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_RENDER_PARAMETERS_HPP_INCLUDED

#include <sanguis/client/draw2d/translation.hpp>
#include <sanguis/client/draw2d/scene/world/render_parameters_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{
namespace world
{

class render_parameters
{
	FCPPT_NONASSIGNABLE(
		render_parameters
	);
public:
	render_parameters(
		sge::renderer::context::core &,
		sanguis::client::draw2d::translation
	);

	sge::renderer::context::core &
	render_context() const;

	sanguis::client::draw2d::translation
	translation() const;
private:
	sge::renderer::context::core &render_context_;

	sanguis::client::draw2d::translation const translation_;
};

}
}
}
}
}

#endif
