#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_CLIENT_CATEGORY_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_CLIENT_CATEGORY_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/client/category_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis::client::draw2d::sprite::client
{

enum class category : std::uint8_t
{
  background,
  light
};

}

#endif
