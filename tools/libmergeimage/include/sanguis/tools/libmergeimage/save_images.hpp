#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_SAVE_IMAGES_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_SAVE_IMAGES_HPP_INCLUDED

#include <sanguis/tools/libmergeimage/image_vector.hpp>
#include <sanguis/tools/libmergeimage/saved_image_vector.hpp>
#include <sanguis/tools/libmergeimage/symbol.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sanguis::tools::libmergeimage
{

[[nodiscard]]
SANGUIS_TOOLS_LIBMERGEIMAGE_SYMBOL
sanguis::tools::libmergeimage::saved_image_vector
save_images(
	sge::image2d::system &, // NOLINT(google-runtime-references)
	std::filesystem::path const &,
	sanguis::tools::libmergeimage::image_vector const &
);

}

#endif
