#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_PATH_COUNT_PAIR_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_PATH_COUNT_PAIR_HPP_INCLUDED

#include <sanguis/tools/libmergeimage/count_type.hpp>
#include <sanguis/tools/libmergeimage/path.hpp>
#include <sanguis/tools/libmergeimage/path_count_pair_fwd.hpp>
#include <sanguis/tools/libmergeimage/symbol.hpp>

namespace sanguis::tools::libmergeimage
{

class path_count_pair
{
public:
  path_count_pair(
      sanguis::tools::libmergeimage::path &&, sanguis::tools::libmergeimage::count_type);

  [[nodiscard]] SANGUIS_TOOLS_LIBMERGEIMAGE_SYMBOL sanguis::tools::libmergeimage::path const &
  path() const;

  [[nodiscard]] SANGUIS_TOOLS_LIBMERGEIMAGE_SYMBOL sanguis::tools::libmergeimage::count_type
  count() const;

private:
  sanguis::tools::libmergeimage::path path_;

  sanguis::tools::libmergeimage::count_type count_;
};

}

#endif
