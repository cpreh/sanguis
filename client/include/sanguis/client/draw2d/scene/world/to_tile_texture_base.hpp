#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TO_TILE_TEXTURE_BASE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TO_TILE_TEXTURE_BASE_HPP_INCLUDED

#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/load/tiles/const_optional_texture_container_ref.hpp>
#include <sge/texture/const_optional_part_ref.hpp>
#include <sge/texture/part_fwd.hpp>


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

template<
	typename DebugMessage
>
sge::texture::const_optional_part_ref const
to_tile_texture_base(
	sanguis::client::load::tiles::const_optional_texture_container_ref const &_textures,
	sanguis::client::draw::debug const _debug,
	sge::texture::part const &_default,
	DebugMessage const &_debug_message
)
{
	if(
		!_textures
		||
		_textures->empty()
	)
	{
		_debug_message();

		return
			_debug.get()
			?
				sge::texture::const_optional_part_ref{
					_default
				}
			:
				sge::texture::const_optional_part_ref{}
			;
	}

	// TODO: Make this random
	return
		sge::texture::const_optional_part_ref{
			*_textures->at(
				0u
			)
		};
}

}
}
}
}
}

#endif
