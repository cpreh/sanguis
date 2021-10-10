#ifndef SANGUIS_TILES_IMPL_LOAD_FILE_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_LOAD_FILE_HPP_INCLUDED

#include <sge/image2d/optional_file_unique_ptr.hpp>
#include <sge/image2d/system_ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

namespace sanguis::tiles::impl
{

sge::image2d::optional_file_unique_ptr
load_file(sge::image2d::system_ref, std::filesystem::path const &);

}

#endif
