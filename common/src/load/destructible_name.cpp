#include <sanguis/creator/destructible_type.hpp>
#include <sanguis/load/destructible_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

fcppt::string sanguis::load::destructible_name(sanguis::creator::destructible_type const _type)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_type)
  {
  case sanguis::creator::destructible_type::barrel:
    return FCPPT_TEXT("barrel");
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_type);
}
