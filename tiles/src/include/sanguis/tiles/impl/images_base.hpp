#ifndef SANGUIS_TILES_IMPL_IMAGES_BASE_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_IMAGES_BASE_HPP_INCLUDED

#include <sanguis/tiles/area_container.hpp>
#include <sanguis/tiles/collection.hpp>
#include <sanguis/tiles/content.hpp>
#include <sanguis/tiles/error.hpp>
#include <sanguis/tiles/orientation.hpp>
#include <sanguis/tiles/pair.hpp>
#include <sanguis/tiles/set.hpp>
#include <sanguis/tiles/impl/content_path.hpp>
#include <sanguis/tiles/impl/error_message_function.hpp>
#include <sanguis/tiles/impl/optional_content_path.hpp>
#include <sanguis/tiles/impl/orientation_to_string.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>


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
images_base(
	fcppt::log::object &_log,
	sanguis::tiles::collection &_collection,
	sanguis::tiles::error const _error_code,
	sanguis::tiles::pair<
		Tile
	> const _pair,
	sanguis::tiles::orientation const _orientation,
	sanguis::tiles::impl::error_message_function const &_error_message
)
{
	sanguis::tiles::set<
		Tile
	> const &cur_set(
		_collection.set(
			_pair
		)
	);

	return
		fcppt::optional::maybe(
			fcppt::container::find_opt_mapped(
				cur_set.orientations(),
				_orientation
			),
			[
				&cur_set,
				&_log,
				&_error_message,
				_error_code,
				_orientation
			]{

				FCPPT_LOG_DEBUG(
					_log,
					fcppt::log::_
						<<
						FCPPT_TEXT("Orientation ")
						<<
						sanguis::tiles::impl::orientation_to_string(
							_orientation
						)
						<<
						FCPPT_TEXT(" not found in ")
						<<
						fcppt::filesystem::path_to_string(
							cur_set.path()
						)
						<<
						FCPPT_TEXT(" from ")
						<<
						_error_message()
				);

				return
					sanguis::tiles::impl::optional_content_path(
						sanguis::tiles::impl::content_path(
							sanguis::tiles::content(
								_error_code
							),
							fcppt::make_cref(
								cur_set.path()
							)
						)
					);
			},
			[
				&_log,
				&cur_set,
				&_error_message
			](
				fcppt::reference<
					sanguis::tiles::area_container const
				> const _images
			)
			{
				if(
					_images.get().empty()
				)
				{
					FCPPT_LOG_ERROR(
						_log,
						fcppt::log::_
							<<
							FCPPT_TEXT("Zero textures in ")
							<<
							fcppt::filesystem::path_to_string(
								cur_set.path()
							)
							<<
							FCPPT_TEXT(" from ")
							<<
							_error_message()
					);

					return
						sanguis::tiles::impl::optional_content_path();
				}

				return
					sanguis::tiles::impl::optional_content_path(
						sanguis::tiles::impl::content_path(
							sanguis::tiles::content(
								_images
							),
							fcppt::make_cref(
								cur_set.path()
							)
						)
					);
			}
		);
}

}
}
}

#endif
