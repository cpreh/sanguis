#include <sanguis/client/load/resource/textures.hpp>
#include <sanguis/client/load/tiles/context.hpp>
#include <sanguis/client/load/tiles/set.hpp>
#include <sanguis/client/load/tiles/texture_container.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <sanguis/tiles/area_container_ref_fwd.hpp>
#include <sanguis/tiles/collection.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/container/get_or_insert.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::client::load::tiles::context::context(
	sanguis::client::load::resource::textures const &_textures
)
:
	collection_(
		_textures.image_system()
	),
	textures_(
		_textures
	),
	sets_(),
	missing_texture_(
		_textures.make_missing_texture(
			sanguis::creator::tile_size::value,
			sge::image::color::predef::black(),
			sge::image::color::predef::magenta()
		)
	),
	missing_background_texture_(
		_textures.make_missing_texture(
			sanguis::creator::tile_size::value,
			sge::image::color::predef::white(),
			sge::image::color::predef::green()
		)
	),
	missing_object_texture_(
		_textures.make_missing_texture(
			sanguis::creator::tile_size::value,
			sge::image::color::predef::white(),
			sge::image::color::predef::blue()
		)
	)
{
}

sanguis::client::load::tiles::context::~context()
{
}

sanguis::client::load::tiles::texture_container const &
sanguis::client::load::tiles::context::set(
	boost::filesystem::path const &_image_path,
	sanguis::tiles::area_container_ref const &_areas
)
{
	return
		fcppt::container::get_or_insert(
			sets_,
			_image_path,
			[
				this
			](
				boost::filesystem::path const &_path
			)
			{
				return
					sanguis::client::load::tiles::set(
						textures_,
						_path
					);
			}
		).areas(
			_areas
		);
}

sanguis::tiles::collection &
sanguis::client::load::tiles::context::collection()
{
	return
		collection_;
}

sge::texture::part const &
sanguis::client::load::tiles::context::missing_texture() const
{
	return
		*missing_texture_;
}

sge::texture::part const &
sanguis::client::load::tiles::context::missing_background_texture() const
{
	return
		*missing_background_texture_;
}

sge::texture::part const &
sanguis::client::load::tiles::context::missing_object_texture() const
{
	return
		*missing_object_texture_;
}
