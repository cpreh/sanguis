#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_IMPL_CALC_CELL_SIZE_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_IMPL_CALC_CELL_SIZE_HPP_INCLUDED

#include <sanguis/tools/libmergeimage/impl/cell_size.hpp>
#include <sanguis/tools/libmergeimage/impl/path_vector_vector.hpp>
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

sanguis::tools::libmergeimage::impl::cell_size
calc_cell_size(
	sge::image2d::system &,
	std::filesystem::path const &,
	sanguis::tools::libmergeimage::impl::path_vector_vector const &
);

}
}
}
}

#endif
