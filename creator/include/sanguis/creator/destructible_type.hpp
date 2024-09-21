#ifndef SANGUIS_CREATOR_DESTRUCTIBLE_TYPE_HPP_INCLUDED
#define SANGUIS_CREATOR_DESTRUCTIBLE_TYPE_HPP_INCLUDED

#include <sanguis/creator/destructible_type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>

namespace sanguis::creator
{

// NOLINTNEXTLINE(performance-enum-size)
enum class destructible_type
{
  barrel
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sanguis::creator::destructible_type::barrel);

#endif
