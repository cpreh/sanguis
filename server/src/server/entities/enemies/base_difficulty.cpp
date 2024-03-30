#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/entities/enemies/base_difficulty.hpp>
#include <sanguis/server/entities/enemies/difficulty_value.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sanguis::server::entities::enemies::difficulty_value
sanguis::server::entities::enemies::base_difficulty(sanguis::creator::enemy_type const _enemy_type)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_enemy_type)
  {
  case sanguis::creator::enemy_type::wolf_black:
  case sanguis::creator::enemy_type::wolf_brown:
  case sanguis::creator::enemy_type::wolf_white:
    return fcppt::literal<sanguis::server::entities::enemies::difficulty_value>(3);
  // NOLINTNEXTLINE(bugprone-branch-clone)
  case sanguis::creator::enemy_type::zombie00:
    return fcppt::literal<sanguis::server::entities::enemies::difficulty_value>(2);
  case sanguis::creator::enemy_type::zombie01:
    return fcppt::literal<sanguis::server::entities::enemies::difficulty_value>(2);
  case sanguis::creator::enemy_type::spider:
    return fcppt::literal<sanguis::server::entities::enemies::difficulty_value>(
        5 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    );
  case sanguis::creator::enemy_type::skeleton:
    return fcppt::literal<sanguis::server::entities::enemies::difficulty_value>(
        8 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    );
  case sanguis::creator::enemy_type::ghost:
    return fcppt::literal<sanguis::server::entities::enemies::difficulty_value>(
        5 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    );
  case sanguis::creator::enemy_type::maggot:
    return fcppt::literal<sanguis::server::entities::enemies::difficulty_value>(1);
  case sanguis::creator::enemy_type::reaper:
    return fcppt::literal<sanguis::server::entities::enemies::difficulty_value>(
        20 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    );
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_enemy_type);
}
