#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_LOG_TILE_ERROR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_LOG_TILE_ERROR_HPP_INCLUDED

#include <sanguis/client/draw2d/log.hpp>
#include <fcppt/log/debug.hpp>


#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_LOG_TILE_ERROR(\
	message\
) \
FCPPT_LOG_DEBUG(\
	sanguis::client::draw2d::log(),\
	message\
)

#endif
