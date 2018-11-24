#ifndef SANGUIS_TILES_IMPL_CONNECTING_IMAGES_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_CONNECTING_IMAGES_HPP_INCLUDED

#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_grid.hpp>
#include <sanguis/tiles/collection_fwd.hpp>
#include <sanguis/tiles/error.hpp>
#include <sanguis/tiles/pair.hpp>
#include <sanguis/tiles/impl/error_message_function.hpp>
#include <sanguis/tiles/impl/filter_connecting.hpp>
#include <sanguis/tiles/impl/images_base.hpp>
#include <sanguis/tiles/impl/make_neighbors.hpp>
#include <sanguis/tiles/impl/make_pair.hpp>
#include <sanguis/tiles/impl/make_orientation.hpp>
#include <sanguis/tiles/impl/neighbors.hpp>
#include <sanguis/tiles/impl/neighbors_to_string.hpp>
#include <sanguis/tiles/impl/optional_content_path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sanguis
{
namespace tiles
{
namespace impl
{

template<
	typename Tile
>
sanguis::tiles::impl::optional_content_path
connecting_images(
	fcppt::log::object &_log,
	sanguis::tiles::collection &_collection,
	sanguis::tiles::error const _error_code,
	sanguis::creator::tile_grid<
		Tile
	> const &_grid,
	sanguis::creator::pos const _pos
)
{
	sanguis::tiles::impl::neighbors<
		Tile
	> const neighbors(
		sanguis::tiles::impl::make_neighbors(
			_grid,
			_pos
		)
	);

	return
		fcppt::optional::maybe(
			sanguis::tiles::impl::make_pair(
				neighbors
			),
			[
				&_log,
				&neighbors
			]
			{
				FCPPT_LOG_ERROR(
					_log,
					fcppt::log::out
						<<
						FCPPT_TEXT("Tile combination ")
						<<
						sanguis::tiles::impl::neighbors_to_string(
							neighbors
						)
						<<
						FCPPT_TEXT(" consists of too many tiles.")
				)

				return
					sanguis::tiles::impl::optional_content_path();
			},
			[
				_error_code,
				&_log,
				&_collection,
				&neighbors
			](
				sanguis::tiles::pair<
					Tile
				> const _pair
			)
			{
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wattributes)
				return
					sanguis::tiles::impl::filter_connecting(
						_pair
					)
					?
						sanguis::tiles::impl::optional_content_path{}
					:
						sanguis::tiles::impl::images_base(
							_log,
							_collection,
							_error_code,
							_pair,
							sanguis::tiles::impl::make_orientation(
								_pair,
								neighbors
							),
							sanguis::tiles::impl::error_message_function{
								[
									&neighbors
								]{
									return
										sanguis::tiles::impl::neighbors_to_string(
											neighbors
										);
								}
							}
						)
					;
FCPPT_PP_POP_WARNING
			}
		);
}

}
}
}

#endif
