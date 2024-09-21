#ifndef SANGUIS_PERK_TYPE_HPP_INCLUDED
#define SANGUIS_PERK_TYPE_HPP_INCLUDED

#include <sanguis/perk_type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{

enum class perk_type : std::uint8_t
{
  choleric,
  health,
  fire_damage,
  piercing_damage,
  ias,
  ims,
  irs
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sanguis::perk_type::irs);

#endif
