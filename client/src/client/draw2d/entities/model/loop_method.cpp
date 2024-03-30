#include <sanguis/client/draw2d/entities/model/loop_method.hpp>
#include <sanguis/client/draw2d/sprite/animation/loop_method.hpp>
#include <sanguis/client/load/animation_type.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sanguis::client::draw2d::sprite::animation::loop_method
sanguis::client::draw2d::entities::model::loop_method(
    sanguis::client::load::animation_type const _atype)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
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
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_atype);
}
