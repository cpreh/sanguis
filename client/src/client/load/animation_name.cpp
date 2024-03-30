#include <sanguis/client/load/animation_name.hpp>
#include <sanguis/client/load/animation_type.hpp>
#include <sanguis/model/animation_name.hpp>
#include <fcppt/text.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sanguis::model::animation_name
sanguis::client::load::animation_name(sanguis::client::load::animation_type const _type)
{
#define SANGUIS_LOAD_ANIMATION_NAME_CASE(name) \
  case sanguis::client::load::animation_type::name: \
    return sanguis::model::animation_name(FCPPT_TEXT(#name))

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_type)
  {
    SANGUIS_LOAD_ANIMATION_NAME_CASE(none);
    SANGUIS_LOAD_ANIMATION_NAME_CASE(attacking);
    SANGUIS_LOAD_ANIMATION_NAME_CASE(walking);
    SANGUIS_LOAD_ANIMATION_NAME_CASE(dying);
    SANGUIS_LOAD_ANIMATION_NAME_CASE(deploying);
    SANGUIS_LOAD_ANIMATION_NAME_CASE(reloading);
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_type);

#undef SANGUIS_LOAD_ANIMATION_NAME_CASE
}
