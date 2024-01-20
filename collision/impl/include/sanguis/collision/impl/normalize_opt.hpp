#ifndef SANGUIS_COLLISION_IMPL_NORMALIZE_OPT_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_NORMALIZE_OPT_HPP_INCLUDED

#include <sanguis/collision/impl/is_null.hpp>
#include <fcppt/not.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/vector/arithmetic.hpp> // IWYU pragma: keep
#include <fcppt/math/vector/length.hpp>
#include <fcppt/math/vector/object.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/optional/join.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/object_impl.hpp>

namespace sanguis::collision::impl
{

template <typename T, fcppt::math::size_type N, typename S>
inline fcppt::optional::object<fcppt::math::vector::static_<T, N>>
normalize_opt(fcppt::math::vector::object<T, N, S> const _vec)
{
  T const length{fcppt::math::vector::length(_vec)};

  return fcppt::optional::join(fcppt::optional::make_if(
      fcppt::not_(sanguis::collision::impl::is_null(length)),
      [_vec, length] { return _vec / length; }));
}

}

#endif
