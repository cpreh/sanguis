#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_ANIMATION_SERIES_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_ANIMATION_SERIES_HPP_INCLUDED

#include <sanguis/client/load/resource/animation/entity.hpp> // IWYU pragma: keep
#include <sanguis/client/load/resource/animation/entity_vector.hpp>
#include <sanguis/client/load/resource/animation/series_fwd.hpp> // IWYU pragma: keep
#include <fcppt/noncopyable.hpp>

namespace sanguis::client::load::resource::animation
{

class series
{
  FCPPT_NONCOPYABLE(series);

public:
  using const_iterator = sanguis::client::load::resource::animation::entity_vector::const_iterator;

  explicit series(sanguis::client::load::resource::animation::entity_vector &&);

  series(series &&) noexcept;

  series &operator=(series &&) noexcept;

  ~series();

  [[nodiscard]] sanguis::client::load::resource::animation::entity_vector const &entities() const;

  [[nodiscard]] const_iterator begin() const;

  [[nodiscard]] const_iterator end() const;

private:
  sanguis::client::load::resource::animation::entity_vector entities_;
};

}

#endif
