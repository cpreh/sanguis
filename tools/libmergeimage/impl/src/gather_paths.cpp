#include <sanguis/tools/libmergeimage/impl/gather_paths.hpp>
#include <sanguis/tools/libmergeimage/impl/path_vector.hpp>
#include <sanguis/tools/libmergeimage/impl/path_vector_vector.hpp>
#include <sanguis/tools/libmergeimage/impl/tree_depth.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/iterator/make_range.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

sanguis::tools::libmergeimage::impl::path_vector_vector
sanguis::tools::libmergeimage::impl::gather_paths(std::filesystem::path const &_base_path)
{
  sanguis::tools::libmergeimage::impl::path_vector_vector result;

  for (std::filesystem::recursive_directory_iterator it(_base_path);
       it != std::filesystem::recursive_directory_iterator();
       ++it)
  {
    if (fcppt::cast::to_unsigned(it.depth()) ==
            sanguis::tools::libmergeimage::impl::tree_depth::value - 1 &&
        it.recursion_pending())
    {
      it.disable_recursion_pending();

      sanguis::tools::libmergeimage::impl::path_vector temp;

      for (std::filesystem::path const &path : fcppt::iterator::make_range(
               std::filesystem::directory_iterator(*it), std::filesystem::directory_iterator()))
      {
        temp.push_back(std::filesystem::relative(path, _base_path));
      }

      result.push_back(temp);
    }
  }

  return result;
}
