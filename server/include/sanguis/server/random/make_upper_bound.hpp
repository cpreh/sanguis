#ifndef SANGUIS_SERVER_RANDOM_MAKE_UPPER_BOUND_HPP_INCLUDED
#define SANGUIS_SERVER_RANDOM_MAKE_UPPER_BOUND_HPP_INCLUDED

#include <sanguis/exception.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>
#include <fcppt/random/distribution/parameters/uniform_real.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::random
{

template <typename T, typename Enable = void>
struct make_upper_bound;

template <typename T>
struct make_upper_bound<T, std::enable_if_t<std::is_floating_point_v<typename T::value_type>>>
{
  using result_type = typename fcppt::random::distribution::parameters::uniform_real<T>::sup;

  static result_type execute(T const _value) { return result_type(_value); }
};

template <typename T>
struct make_upper_bound<
    T,
    std::enable_if_t<std::negation_v<std::is_floating_point<typename T::value_type>>>>
{
  using result_type = typename fcppt::random::distribution::parameters::uniform_int<T>::max;

  static result_type execute(T const _value)
  {
    if (_value <= fcppt::literal<T>(0))
    {
      throw sanguis::exception{FCPPT_TEXT("make_upper_bound: value <= 0")};
    }

    return result_type(_value - fcppt::literal<T>(1));
  }
};

}

#endif
