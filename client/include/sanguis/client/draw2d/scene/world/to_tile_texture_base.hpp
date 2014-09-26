#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TO_TILE_TEXTURE_BASE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TO_TILE_TEXTURE_BASE_HPP_INCLUDED

#include <sanguis/random_generator.hpp>
#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/load/tiles/const_optional_texture_container_ref.hpp>
#include <sanguis/client/load/tiles/texture_container.hpp>
#include <sge/texture/const_optional_part_ref.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/random/distribution/make_basic.hpp>
#include <fcppt/random/distribution/parameters/make_uniform_indices.hpp>


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
	sanguis::random_generator &_random_generator,
	sanguis::client::load::tiles::const_optional_texture_container_ref const &_opt_textures,
	sanguis::client::draw::debug const _debug,
	sge::texture::part const &_default,
	DebugMessage const &_debug_message
)
{
	auto const make_default(
		[
			&_debug_message,
			&_default,
			_debug
		]{
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
	);

	return
		fcppt::maybe(
			_opt_textures,
			make_default,
			[
				&_random_generator,
				make_default
			](
				sanguis::client::load::tiles::texture_container const &_textures
			)
			{
				// TODO: Create an optional distribution for this
				return
					_textures.empty()
					?
						make_default()
					:
						sge::texture::const_optional_part_ref{
							*_textures[
								fcppt::random::distribution::make_basic(
									fcppt::random::distribution::parameters::make_uniform_indices(
										_textures
									)
								)(
									_random_generator
								)
							]
						};
			}
		);
}

}
}
}
}
}

#endif
