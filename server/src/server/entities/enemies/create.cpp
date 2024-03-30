#include <sanguis/random_generator_ref.hpp>
#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/entities/spawn_owner_fwd.hpp>
#include <sanguis/server/entities/with_id.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/entities/enemies/base_difficulty.hpp>
#include <sanguis/server/entities/enemies/create.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/difficulty_value.hpp>
#include <sanguis/server/entities/enemies/special_chance.hpp>
#include <sanguis/server/entities/enemies/factory/ghost.hpp>
#include <sanguis/server/entities/enemies/factory/maggot.hpp>
#include <sanguis/server/entities/enemies/factory/parameters.hpp>
#include <sanguis/server/entities/enemies/factory/reaper.hpp>
#include <sanguis/server/entities/enemies/factory/skeleton.hpp>
#include <sanguis/server/entities/enemies/factory/spider.hpp>
#include <sanguis/server/entities/enemies/factory/wolf.hpp>
#include <sanguis/server/entities/enemies/factory/zombie00.hpp>
#include <sanguis/server/entities/enemies/factory/zombie01.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/weapons/common_parameters_fwd.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sanguis::server::entities::with_id_unique_ptr sanguis::server::entities::enemies::create(
    sanguis::random_generator_ref const _random_generator,
    sanguis::server::weapons::common_parameters const &_weapons_parameters,
    sanguis::creator::enemy_type const _enemy_type,
    sanguis::creator::enemy_kind const _enemy_kind,
    sanguis::server::world::difficulty const _difficulty,
    sanguis::server::environment::load_context &_load_context,
    sanguis::server::entities::spawn_owner const &_spawn,
    sanguis::server::entities::enemies::special_chance const _special_chance)
{
  sanguis::server::entities::enemies::factory::parameters const parameters{
      _random_generator,
      _weapons_parameters,
      _enemy_type,
      _enemy_kind,
      sanguis::server::entities::enemies::difficulty(
          sanguis::server::entities::enemies::base_difficulty(_enemy_type) *
          fcppt::cast::int_to_float<sanguis::server::entities::enemies::difficulty_value>(
              _difficulty.get())),
      _load_context,
      _spawn,
      _special_chance};

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_enemy_type)
  {
  case sanguis::creator::enemy_type::zombie00:
    return sanguis::server::entities::enemies::factory::zombie00(parameters);
  case sanguis::creator::enemy_type::zombie01:
    return sanguis::server::entities::enemies::factory::zombie01(parameters);
  case sanguis::creator::enemy_type::wolf_black:
  case sanguis::creator::enemy_type::wolf_brown:
  case sanguis::creator::enemy_type::wolf_white:
    return sanguis::server::entities::enemies::factory::wolf(parameters);
  case sanguis::creator::enemy_type::skeleton:
    return sanguis::server::entities::enemies::factory::skeleton(parameters);
  case sanguis::creator::enemy_type::maggot:
    return sanguis::server::entities::enemies::factory::maggot(parameters);
  case sanguis::creator::enemy_type::ghost:
    return sanguis::server::entities::enemies::factory::ghost(parameters);
  case sanguis::creator::enemy_type::spider:
    return sanguis::server::entities::enemies::factory::spider(parameters);
  case sanguis::creator::enemy_type::reaper:
    return sanguis::server::entities::enemies::factory::reaper(parameters);
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_enemy_type);
}
