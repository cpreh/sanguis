#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_BACKGROUND_DIM_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_BACKGROUND_DIM_HPP_INCLUDED

#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/device/core_fwd.hpp>


namespace sanguis::client::draw2d::scene
{

sge::renderer::screen_size
background_dim(
	sge::renderer::device::core & // NOLINT(google-runtime-references)
); // NOLINT(google-runtime-references)

}

#endif
