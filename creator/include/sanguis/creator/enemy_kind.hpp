#ifndef SANGUIS_CREATOR_ENEMY_KIND_HPP_INCLUDED
#define SANGUIS_CREATOR_ENEMY_KIND_HPP_INCLUDED

#include <sanguis/creator/enemy_kind_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis::creator
{

enum class enemy_kind : std::uint8_t
{
  normal,
  unique,
  boss
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sanguis::creator::enemy_kind::boss);

#endif
