#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/sprite/normal/no_rotation.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_literal_strong_typedef.hpp> // NOLINT(misc-include-cleaner)

sanguis::client::draw2d::sprite::rotation sanguis::client::draw2d::sprite::normal::no_rotation()
{
  return fcppt::literal<sanguis::client::draw2d::sprite::rotation>(0);
}
