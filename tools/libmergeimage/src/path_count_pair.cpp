#include <sanguis/tools/libmergeimage/count_type.hpp>
#include <sanguis/tools/libmergeimage/path.hpp>
#include <sanguis/tools/libmergeimage/path_count_pair.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::tools::libmergeimage::path_count_pair::path_count_pair(
    sanguis::tools::libmergeimage::path &&_path,
    sanguis::tools::libmergeimage::count_type const _count)
    : path_(std::move(_path)), count_(_count)
{
}

sanguis::tools::libmergeimage::path const &
sanguis::tools::libmergeimage::path_count_pair::path() const
{
  return path_;
}

sanguis::tools::libmergeimage::count_type
sanguis::tools::libmergeimage::path_count_pair::count() const
{
  return count_;
}
