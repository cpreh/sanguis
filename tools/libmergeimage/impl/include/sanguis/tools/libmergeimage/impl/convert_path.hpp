#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_IMPL_CONVERT_PATH_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_IMPL_CONVERT_PATH_HPP_INCLUDED

#include <sanguis/tools/libmergeimage/path.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sanguis::tools::libmergeimage::impl
{

sanguis::tools::libmergeimage::path
convert_path(
	std::filesystem::path const &
);

}

#endif
