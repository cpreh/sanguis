#ifndef SANGUIS_AOE_PROJECTILE_TYPE_HPP_INCLUDED
#define SANGUIS_AOE_PROJECTILE_TYPE_HPP_INCLUDED

#include <sanguis/aoe_projectile_type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{

enum class aoe_projectile_type : std::uint8_t
{
  rocket,
  grenade
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sanguis::aoe_projectile_type::grenade);

#endif
