#include <sanguis/tools/libmergeimage/image.hpp>
#include <sanguis/tools/libmergeimage/image_store.hpp>
#include <sanguis/tools/libmergeimage/path_count_pair_vector.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::tools::libmergeimage::image::image(
    sanguis::tools::libmergeimage::path_count_pair_vector &&_paths,
    sanguis::tools::libmergeimage::image_store &&_store)
    : paths_(std::move(_paths)), store_(std::move(_store))
{
}

sanguis::tools::libmergeimage::image::image(image &&) noexcept = default;

sanguis::tools::libmergeimage::image &
sanguis::tools::libmergeimage::image::operator=(image &&) noexcept = default;

sanguis::tools::libmergeimage::image::~image() = default;

sanguis::tools::libmergeimage::path_count_pair_vector const &
sanguis::tools::libmergeimage::image::paths() const
{
  return paths_;
}

sanguis::tools::libmergeimage::image_store const &
sanguis::tools::libmergeimage::image::store() const
{
  return store_;
}
