#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_IMPL_MAKE_IMAGE_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_IMPL_MAKE_IMAGE_HPP_INCLUDED

#include <sanguis/tools/libmergeimage/image.hpp>
#include <sanguis/tools/libmergeimage/impl/cell_size.hpp>
#include <sanguis/tools/libmergeimage/impl/path_vector.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tools
{
namespace libmergeimage
{
namespace impl
{

sanguis::tools::libmergeimage::image
make_image(
	sge::image2d::system &, // NOLINT(google-runtime-references)
	std::filesystem::path const &,
	sanguis::tools::libmergeimage::impl::cell_size const &,
	sanguis::tools::libmergeimage::impl::path_vector
);

}
}
}
}

#endif
