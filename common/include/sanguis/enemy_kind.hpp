#ifndef SANGUIS_ENEMY_KIND_HPP_INCLUDED
#define SANGUIS_ENEMY_KIND_HPP_INCLUDED

#include <sanguis/enemy_kind_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{

enum class enemy_kind : std::uint8_t
{
  normal,
  champion,
  unique,
  boss,
  fcppt_maximum = boss
};

}

#endif
