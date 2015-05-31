#include <sanguis/client/load/resource/texture_from_view.hpp>
#include <sanguis/client/load/resource/textures.hpp>
#include <sanguis/client/load/tiles/context.hpp>
#include <sanguis/client/load/tiles/set.hpp>
#include <sanguis/client/load/tiles/texture_container.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <sanguis/tiles/area_container_ref_fwd.hpp>
#include <sanguis/tiles/collection.hpp>
#include <sanguis/tiles/error.hpp>
#include <sanguis/tiles/error_image.hpp>
#include <sge/image2d/store/view.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/algorithm/enum_array_fold.hpp>
#include <fcppt/container/enum_array_impl.hpp>
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
	missing_textures_(
		fcppt::algorithm::enum_array_fold<
			missing_texture_array
		>(
			[
				&_textures
			](
				sanguis::tiles::error const _error
			)
			{
				return
					sanguis::client::load::resource::texture_from_view(
						_textures.renderer(),
						sge::image2d::store::view(
							sanguis::tiles::error_image(
								_error
							)
						)
					);
			}
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
sanguis::client::load::tiles::context::missing_texture(
	sanguis::tiles::error const _error
) const
{
	return
		*missing_textures_[
			_error
		];
}
