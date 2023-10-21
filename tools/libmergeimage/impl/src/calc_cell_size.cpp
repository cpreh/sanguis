#include <sanguis/tools/libmergeimage/exception.hpp>
#include <sanguis/tools/libmergeimage/impl/calc_cell_size.hpp>
#include <sanguis/tools/libmergeimage/impl/cell_size.hpp>
#include <sanguis/tools/libmergeimage/impl/path_vector_vector.hpp>
#include <sge/image/exception.hpp>
#include <sge/image2d/file.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image2d/load_exn.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

sanguis::tools::libmergeimage::impl::cell_size sanguis::tools::libmergeimage::impl::calc_cell_size(
    sge::image2d::system &_image_system,
    std::filesystem::path const &_base_path,
    sanguis::tools::libmergeimage::impl::path_vector_vector const &_paths)
try
{
  if (_paths.empty())
  {
    throw sanguis::tools::libmergeimage::exception{FCPPT_TEXT("paths is empty")};
  }

  return sanguis::tools::libmergeimage::impl::cell_size(
      sge::image2d::load_exn(fcppt::make_ref(_image_system), _base_path / _paths[0].at(0))->size());
}
catch (sge::image::exception const &_error)
{
  throw sanguis::tools::libmergeimage::exception{
      FCPPT_TEXT("Couldn't load an image to determine the cell size: ") + _error.string()};
}
