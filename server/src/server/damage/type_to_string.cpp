#include <sanguis/server/damage/type.hpp>
#include <sanguis/server/damage/type_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

fcppt::string sanguis::server::damage::type_to_string(sanguis::server::damage::type const _type)
{
#define SANGUIS_SERVER_DAMAGE_TYPE_TO_STRING_CASE(name) \
  case sanguis::server::damage::type::name: \
    return FCPPT_TEXT(#name)

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_type)
  {
    SANGUIS_SERVER_DAMAGE_TYPE_TO_STRING_CASE(normal);
    SANGUIS_SERVER_DAMAGE_TYPE_TO_STRING_CASE(piercing);
    SANGUIS_SERVER_DAMAGE_TYPE_TO_STRING_CASE(fire);
    SANGUIS_SERVER_DAMAGE_TYPE_TO_STRING_CASE(ice);
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_type);

#undef SANGUIS_SERVER_DAMAGE_TYPE_TO_STRING_CASE
}
