#ifndef SANGUIS_SERVER_RANDOM_SPLIT_HPP_INCLUDED
#define SANGUIS_SERVER_RANDOM_SPLIT_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/random/amount.hpp>
#include <sanguis/server/random/distributor_impl.hpp>
#include <sanguis/server/random/map_with_index.hpp>
#include <sanguis/server/random/max.hpp>
#include <sanguis/server/random/min.hpp>
#include <sanguis/server/random/split_array.hpp>
#include <fcppt/make_literal_strong_typedef.hpp> // IWYU pragma: keep
#include <fcppt/algorithm/repeat.hpp>
#include <fcppt/array/init.hpp>
#include <fcppt/random/distribution/make_basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>
#include <fcppt/type_iso/strong_typedef.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::random
{

template <std::size_t Size>
sanguis::server::random::split_array<Size> split(
    sanguis::random_generator &_random_generator, // NOLINT(google-runtime-references)
    sanguis::server::random::min const _min,
    sanguis::server::random::max const _max,
    sanguis::server::random::split_array<Size> const &_sizes)
{
  using result_type = sanguis::server::random::split_array<Size>;

  using value_type = typename result_type::value_type;

  using size_type = typename result_type::size_type;

  using distributor_type = sanguis::server::random::distributor<value_type, size_type>;

  distributor_type dist(sanguis::server::random::map_with_index(_sizes));

  auto result(
      fcppt::array::init<result_type>([](auto) { return sanguis::server::random::amount(0U); }));

  using size_parameters =
      fcppt::random::distribution::parameters::uniform_int<sanguis::server::random::amount>;

  sanguis::server::random::amount const draws(fcppt::random::distribution::make_basic(
      size_parameters(size_parameters::min(_min.get()), size_parameters::max(_max.get())))(
      _random_generator));

  fcppt::algorithm::repeat(
      draws.get(),
      [&_random_generator, &dist, &result]()
      { ++result.get_unsafe(dist.execute(_random_generator)); });

  return result;
}

}

#endif
