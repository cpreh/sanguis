#ifndef SANGUIS_DOODAD_TYPE_HPP_INCLUDED
#define SANGUIS_DOODAD_TYPE_HPP_INCLUDED

#include <sanguis/doodad_type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{

enum class doodad_type : std::uint8_t
{
  portal_blocker
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sanguis::doodad_type::portal_blocker);

#endif
