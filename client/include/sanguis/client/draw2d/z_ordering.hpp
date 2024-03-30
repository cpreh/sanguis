#ifndef SANGUIS_CLIENT_DRAW2D_Z_ORDERING_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_Z_ORDERING_HPP_INCLUDED

#include <sanguis/client/draw2d/z_ordering_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis::client::draw2d
{

enum class z_ordering : std::uint8_t
{
  ground,
  destructible,
  pickup,
  aura,
  model_generic,
  player_lower,
  bullet_tail,
  bullet,
  player_upper,
  flare,
  text,
  fcppt_maximum = text
};

}

#endif
