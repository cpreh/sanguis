#ifndef SANGUIS_PICKUP_TYPE_HPP_INCLUDED
#define SANGUIS_PICKUP_TYPE_HPP_INCLUDED

#include <sanguis/pickup_type_fwd.hpp> // IWYU pragma: keep

namespace sanguis
{

// NOLINTNEXTLINE(performance-enum-size)
enum class pickup_type
{
  health,
  monster,
  fcppt_maximum = monster
};

}

#endif
