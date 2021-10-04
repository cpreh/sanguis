#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_TRANSLATION_MATRIX_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_TRANSLATION_MATRIX_HPP_INCLUDED

#include <sanguis/client/draw2d/translation_fwd.hpp>
#include <sge/renderer/matrix4.hpp>


namespace sanguis::client::draw2d::scene
{

sge::renderer::matrix4
translation_matrix(
	sanguis::client::draw2d::translation const &
);

}

#endif
