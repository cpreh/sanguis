#include <sanguis/client/draw2d/entities/model/clamp_orientation.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/mod.hpp>
#include <fcppt/config/external_begin.hpp>
#include <numbers>
#include <fcppt/config/external_end.hpp>

sanguis::client::draw2d::sprite::rotation
sanguis::client::draw2d::entities::model::clamp_orientation(
    sanguis::client::draw2d::sprite::rotation const _orientation)
{
  sanguis::client::draw2d::sprite::rotation::value_type const twopi{
      std::numbers::pi_v<sanguis::client::draw2d::sprite::rotation::value_type> *
      fcppt::literal<sanguis::client::draw2d::sprite::rotation::value_type>(2)};

  sanguis::client::draw2d::sprite::rotation::value_type const clamped{
      fcppt::math::mod(_orientation.get(), twopi).get_unsafe()};

  return clamped < fcppt::literal<sanguis::client::draw2d::sprite::rotation::value_type>(0)
             ? sanguis::client::draw2d::sprite::rotation{clamped + twopi}
             : sanguis::client::draw2d::sprite::rotation{clamped};
}
