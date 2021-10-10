#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_SAVED_IMAGE_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_SAVED_IMAGE_HPP_INCLUDED

#include <sanguis/model/image_name.hpp>
#include <sanguis/tools/libmergeimage/path_count_pair_vector.hpp>
#include <sanguis/tools/libmergeimage/saved_image_fwd.hpp>
#include <sanguis/tools/libmergeimage/symbol.hpp>

namespace sanguis::tools::libmergeimage
{

class saved_image
{
public:
  SANGUIS_TOOLS_LIBMERGEIMAGE_SYMBOL
  saved_image(
      sanguis::tools::libmergeimage::path_count_pair_vector &&, sanguis::model::image_name &&);

  [[nodiscard]] SANGUIS_TOOLS_LIBMERGEIMAGE_SYMBOL
      sanguis::tools::libmergeimage::path_count_pair_vector const &
      paths() const;

  [[nodiscard]] SANGUIS_TOOLS_LIBMERGEIMAGE_SYMBOL sanguis::model::image_name const &
  image_name() const;

private:
  sanguis::tools::libmergeimage::path_count_pair_vector paths_;

  sanguis::model::image_name image_name_;
};

}

#endif
