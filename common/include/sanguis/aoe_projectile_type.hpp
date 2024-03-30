#ifndef SANGUIS_AOE_PROJECTILE_TYPE_HPP_INCLUDED
#define SANGUIS_AOE_PROJECTILE_TYPE_HPP_INCLUDED

#include <sanguis/aoe_projectile_type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{

enum class aoe_projectile_type : std::uint8_t
{
  rocket,
  grenade,
  fcppt_maximum = grenade
};

}

#endif
