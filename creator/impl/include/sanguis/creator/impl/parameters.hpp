#ifndef SANGUIS_CREATOR_IMPL_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_PARAMETERS_HPP_INCLUDED

#include <sanguis/creator/opening_count_array.hpp>
#include <sanguis/creator/spawn_boss.hpp>
#include <sanguis/creator/impl/parameters_fwd.hpp> // IWYU pragma: keep
#include <sanguis/creator/impl/random/generator_fwd.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/object_reference.hpp>

namespace sanguis::creator::impl
{

class parameters
{
public:
  parameters(
      fcppt::log::object_reference,
      fcppt::reference<sanguis::creator::impl::random::generator>,
      sanguis::creator::spawn_boss,
      sanguis::creator::opening_count_array);

  [[nodiscard]] fcppt::log::object &log() const;

  [[nodiscard]] sanguis::creator::impl::random::generator &randgen() const;

  [[nodiscard]] sanguis::creator::spawn_boss spawn_boss() const;

  [[nodiscard]] sanguis::creator::opening_count_array const &opening_count_array() const;

private:
  fcppt::log::object_reference log_;

  fcppt::reference<sanguis::creator::impl::random::generator> randgen_;

  sanguis::creator::spawn_boss spawn_boss_;

  sanguis::creator::opening_count_array opening_count_array_;
};

}

#endif
