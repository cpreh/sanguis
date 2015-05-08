#include <sanguis/media_path.hpp>
#include <sanguis/tiles/element_map.hpp>
#include <sanguis/tiles/pair.hpp>
#include <sanguis/tiles/set.hpp>
#include <sanguis/tiles/impl/category.hpp>
#include <sanguis/tiles/impl/instantiate_tile.hpp>
#include <sanguis/tiles/impl/make_element_map.hpp>
#include <sanguis/tiles/impl/name.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system.hpp>
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
			sanguis::tiles::impl::name(
				_pair.first()
			)
			+
			FCPPT_TEXT('_')
			+
			sanguis::tiles::impl::name(
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
sanguis::tiles::element_map const &
sanguis::tiles::set<
	Tile
>::elements() const
{
	return
		elements_;
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
	file_(
		_image_system.load(
			_path
			/
			FCPPT_TEXT("texture.png")
		)
	),
	elements_(
		fcppt::maybe(
			file_,
			[]{
				return
					element_map();
			},
			[
				&_path
			](
				sge::image2d::file_unique_ptr const &_file
			)
			{
				return
					sanguis::tiles::impl::make_element_map(
						_file->view(),
						_path
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
