#ifndef SANGUIS_PICKUP_TYPE_HPP_INCLUDED
#define SANGUIS_PICKUP_TYPE_HPP_INCLUDED

#include <sanguis/pickup_type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>

namespace sanguis
{

// NOLINTNEXTLINE(performance-enum-size)
enum class pickup_type
{
  health,
  monster
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sanguis::pickup_type::monster);

#endif
