#include <sanguis/media_path.hpp>
#include <sanguis/tiles/orientation_map.hpp>
#include <sanguis/tiles/pair.hpp>
#include <sanguis/tiles/set.hpp>
#include <sanguis/tiles/impl/category.hpp>
#include <sanguis/tiles/impl/instantiate_tile.hpp>
#include <sanguis/tiles/impl/load_file.hpp>
#include <sanguis/tiles/impl/make_orientation_map.hpp>
#include <sanguis/tiles/impl/to_string.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/size.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename Tile
>
sanguis::tiles::set<
	Tile
>::set(
	sge::image2d::system &_image_system,
	sanguis::tiles::pair<
		Tile
	> const _pair
)
:
	set(
		_image_system
		,
		sanguis::media_path()
		/
		FCPPT_TEXT("tiles")
		/
		sanguis::tiles::impl::category<
			Tile
		>()
		/
		(
			sanguis::tiles::impl::to_string(
				_pair.first()
			)
			+
			FCPPT_TEXT('_')
			+
			sanguis::tiles::impl::to_string(
				_pair.second()
			)
		)
	)
{
}

template<
	typename Tile
>
sanguis::tiles::set<
	Tile
>::set(
	set &&
)
= default;

template<
	typename Tile
>
sanguis::tiles::set<
	Tile
> &
sanguis::tiles::set<
	Tile
>::operator=(
	set &&
)
= default;

template<
	typename Tile
>
sanguis::tiles::set<
	Tile
>::~set()
{
}

template<
	typename Tile
>
sanguis::tiles::orientation_map const &
sanguis::tiles::set<
	Tile
>::orientations() const
{
	return
		orientations_;
}

template<
	typename Tile
>
boost::filesystem::path const &
sanguis::tiles::set<
	Tile
>::path() const
{
	return
		path_;
}

template<
	typename Tile
>
sanguis::tiles::set<
	Tile
>::set(
	sge::image2d::system &_image_system,
	boost::filesystem::path const &_path
)
:
	path_(
		_path
		/
		FCPPT_TEXT("texture.png")
	),
	orientations_(
		fcppt::maybe(
			sanguis::tiles::impl::load_file(
				_image_system,
				path_
			),
			[]{
				return
					sanguis::tiles::orientation_map();
			},
			[
				&_path
			](
				sge::image2d::file_unique_ptr &&_file
			)
			{
				return
					sanguis::tiles::impl::make_orientation_map(
						_path,
						// TODO: Change sge so that we
						// can query the size without
						// actually loading the whole
						// file
						sge::image2d::view::size(
							_file->view()
						)
					);
			}
		)
	)
{
}

#define SANGUIS_TILES_INSTANTIATE_SET(\
	tile_type\
)\
template \
class \
sanguis::tiles::set<\
	tile_type \
>

SANGUIS_TILES_IMPL_INSTANTIATE_TILE(
	SANGUIS_TILES_INSTANTIATE_SET
);
