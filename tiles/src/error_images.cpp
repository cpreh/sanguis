#include <sanguis/tiles/error.hpp>
#include <sanguis/tiles/error_images.hpp>
#include <sanguis/tiles/error_image_array.hpp>
#include <sanguis/tiles/impl/error_image.hpp>
#include <sanguis/tiles/impl/error_image_colors.hpp>
#include <fcppt/algorithm/enum_array_fold.hpp>


sanguis::tiles::error_image_array
sanguis::tiles::error_images()
{
	return
		fcppt::algorithm::enum_array_fold<
			sanguis::tiles::error_image_array
		>(
			[](
				sanguis::tiles::error const _error
			)
			{
				return
					sanguis::tiles::impl::error_image(
						sanguis::tiles::impl::error_image_colors(
							_error
						)
					);
			}
		);
}
