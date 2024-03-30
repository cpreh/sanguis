#include <sanguis/pickup_type.hpp>
#include <sanguis/load/pickup_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

fcppt::string sanguis::load::pickup_name(sanguis::pickup_type const _type)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_type)
  {
  case sanguis::pickup_type::health:
    return FCPPT_TEXT("hp");
  case sanguis::pickup_type::monster:
    return FCPPT_TEXT("monster");
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_type);
}
