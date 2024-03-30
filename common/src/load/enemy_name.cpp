#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/load/enemy_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

fcppt::string sanguis::load::enemy_name(sanguis::creator::enemy_type const _type)
{
#define SANGUIS_LOAD_ENEMY_NAME_CASE(name) \
  case sanguis::creator::enemy_type::name: \
    return FCPPT_TEXT(#name)

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_type)
  {
    SANGUIS_LOAD_ENEMY_NAME_CASE(wolf_black);
    SANGUIS_LOAD_ENEMY_NAME_CASE(wolf_brown);
    SANGUIS_LOAD_ENEMY_NAME_CASE(wolf_white);
    SANGUIS_LOAD_ENEMY_NAME_CASE(zombie00);
    SANGUIS_LOAD_ENEMY_NAME_CASE(zombie01);
    SANGUIS_LOAD_ENEMY_NAME_CASE(spider);
    SANGUIS_LOAD_ENEMY_NAME_CASE(skeleton);
    SANGUIS_LOAD_ENEMY_NAME_CASE(ghost);
    SANGUIS_LOAD_ENEMY_NAME_CASE(maggot);
    SANGUIS_LOAD_ENEMY_NAME_CASE(reaper);
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_type);

#undef SANGUIS_LOAD_ENEMY_NAME_CASE
}
