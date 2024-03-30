#include <sanguis/friend_type.hpp>
#include <sanguis/load/friend_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

fcppt::string sanguis::load::friend_name(sanguis::friend_type const _type)
{
#define SANGUIS_LOAD_FRIEND_NAME_CASE(name) \
  case sanguis::friend_type::name: \
    return FCPPT_TEXT(#name)

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_type)
  {
    SANGUIS_LOAD_FRIEND_NAME_CASE(spider);
    SANGUIS_LOAD_FRIEND_NAME_CASE(sentry);
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_type);

#undef SANGUIS_LOAD_FRIEND_NAME_CASE
}
