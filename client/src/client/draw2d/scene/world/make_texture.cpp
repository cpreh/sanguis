#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/load/tiles/context.hpp>
#include <sanguis/client/draw2d/scene/world/make_texture.hpp>
#include <sanguis/tiles/area_container_ref.hpp>
#include <sanguis/tiles/content.hpp>
#include <sanguis/tiles/error.hpp>
#include <sge/texture/const_optional_part_ref.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::texture::const_optional_part_ref const
sanguis::client::draw2d::scene::world::make_texture(
	sanguis::random_generator &_random_generator,
	sanguis::client::draw::debug const _debug,
	sanguis::client::load::tiles::context &_context,
	boost::filesystem::path const &_path,
	sanguis::tiles::content const &_content
)
{
	return
		fcppt::variant::match(
			_content,
			[
				&_path,
				&_context
			](
				sanguis::tiles::area_container_ref const &_areas
			)
			{
				sanguis::client::load::tiles::texture_container const &textures(
					_context.set(
						_path,
						_areas
					)
				);

				return
					sge::texture::const_optional_part_ref(
						// FIXME!
						*textures[0]
					);
			},
			[](
				sanguis::tiles::error const _error
			)
			{
				// TODO!
				return
					sge::texture::const_optional_part_ref();
			}
		);
}
