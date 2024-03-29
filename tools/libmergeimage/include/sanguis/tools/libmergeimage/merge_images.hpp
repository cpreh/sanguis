#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_MERGE_IMAGES_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_MERGE_IMAGES_HPP_INCLUDED

#include <sanguis/tools/libmergeimage/merge_result.hpp>
#include <sanguis/tools/libmergeimage/symbol.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

namespace sanguis::tools::libmergeimage
{

SANGUIS_TOOLS_LIBMERGEIMAGE_SYMBOL
sanguis::tools::libmergeimage::merge_result merge_images(
    sge::image2d::system &, // NOLINT(google-runtime-references)
    std::filesystem::path const &);

}

#endif
