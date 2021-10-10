#include <sanguis/client/draw2d/entities/model/loop_method.hpp>
#include <sanguis/client/draw2d/sprite/animation/loop_method.hpp>
#include <sanguis/client/load/animation_type.hpp>
#include <fcppt/assert/unreachable.hpp>

sanguis::client::draw2d::sprite::animation::loop_method
sanguis::client::draw2d::entities::model::loop_method(
    sanguis::client::load::animation_type const _atype)
{
  switch (_atype)
  {
  case sanguis::client::load::animation_type::none:
  case sanguis::client::load::animation_type::walking:
  case sanguis::client::load::animation_type::attacking:
  case sanguis::client::load::animation_type::reloading:
    return sanguis::client::draw2d::sprite::animation::loop_method::repeat;
  case sanguis::client::load::animation_type::dying:
  case sanguis::client::load::animation_type::deploying:
    return sanguis::client::draw2d::sprite::animation::loop_method::stop_at_end;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
