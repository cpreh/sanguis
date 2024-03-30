#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/auras/target_kind.hpp>
#include <sanguis/server/auras/target_kind_to_influence.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sanguis::server::auras::influence sanguis::server::auras::target_kind_to_influence(
    sanguis::server::auras::target_kind const _target_kind)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_target_kind)
  {
  case sanguis::server::auras::target_kind::enemy:
    return sanguis::server::auras::influence::debuff;
  case sanguis::server::auras::target_kind::friend_:
    return sanguis::server::auras::influence::buff;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_target_kind);
}
