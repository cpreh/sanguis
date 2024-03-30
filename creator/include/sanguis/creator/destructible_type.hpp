#ifndef SANGUIS_CREATOR_DESTRUCTIBLE_TYPE_HPP_INCLUDED
#define SANGUIS_CREATOR_DESTRUCTIBLE_TYPE_HPP_INCLUDED

#include <sanguis/creator/destructible_type_fwd.hpp> // IWYU pragma: keep

namespace sanguis::creator
{

// NOLINTNEXTLINE(performance-enum-size)
enum class destructible_type
{
  barrel,
  fcppt_maximum = barrel
};

}

#endif
