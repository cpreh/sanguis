#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_ANIMATION_LOOP_METHOD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_ANIMATION_LOOP_METHOD_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/animation/loop_method_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis::client::draw2d::sprite::animation
{

enum class loop_method : std::uint8_t
{
  repeat,
  stop_at_end
};

}

#endif
