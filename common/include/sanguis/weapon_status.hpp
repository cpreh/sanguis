#ifndef SANGUIS_WEAPON_STATUS_HPP_INCLUDED
#define SANGUIS_WEAPON_STATUS_HPP_INCLUDED

#include <sanguis/weapon_status_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{

enum class weapon_status : std::uint8_t
{
  nothing,
  attacking,
  reloading
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sanguis::weapon_status::reloading);

#endif
