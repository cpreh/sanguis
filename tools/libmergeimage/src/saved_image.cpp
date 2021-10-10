#include <sanguis/model/image_name.hpp>
#include <sanguis/tools/libmergeimage/path_count_pair_vector.hpp>
#include <sanguis/tools/libmergeimage/saved_image.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::tools::libmergeimage::saved_image::saved_image(
    sanguis::tools::libmergeimage::path_count_pair_vector &&_paths,
    sanguis::model::image_name &&_image_name)
    : paths_(std::move(_paths)), image_name_(std::move(_image_name))
{
}

sanguis::tools::libmergeimage::path_count_pair_vector const &
sanguis::tools::libmergeimage::saved_image::paths() const
{
  return paths_;
}

sanguis::model::image_name const &sanguis::tools::libmergeimage::saved_image::image_name() const
{
  return image_name_;
}
