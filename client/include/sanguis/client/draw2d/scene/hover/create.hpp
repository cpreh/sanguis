#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_CREATE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_CREATE_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/hover/info_fwd.hpp>
#include <sanguis/client/draw2d/scene/hover/base_unique_ptr.hpp>
#include <sanguis/client/draw2d/scene/hover/parameters_fwd.hpp>


namespace sanguis::client::draw2d::scene::hover
{

sanguis::client::draw2d::scene::hover::base_unique_ptr
create(
	sanguis::client::draw2d::scene::hover::parameters const &,
	sanguis::client::draw2d::entities::hover::info const &
);

}

#endif
