#ifndef SANGUIS_SECONDARY_WEAPON_TYPE_HPP_INCLUDED
#define SANGUIS_SECONDARY_WEAPON_TYPE_HPP_INCLUDED

#include <sanguis/secondary_weapon_type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>

namespace sanguis
{

// NOLINTNEXTLINE(performance-enum-size)
enum class secondary_weapon_type
{
  grenade,
  sentry,
  spider
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sanguis::secondary_weapon_type::spider);

#endif
