#ifndef SANGUIS_CREATOR_OPENING_TYPE_HPP_INCLUDED
#define SANGUIS_CREATOR_OPENING_TYPE_HPP_INCLUDED

#include <sanguis/creator/opening_type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis::creator
{

enum class opening_type : std::uint8_t
{
  entry,
  exit
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sanguis::creator::opening_type::exit);

#endif
