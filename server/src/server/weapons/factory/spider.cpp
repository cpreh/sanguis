#include <sanguis/duration_second.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/damage/full.hpp>
#include <sanguis/server/damage/make_array.hpp>
#include <sanguis/server/damage/normal.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/common_parameters.hpp>
#include <sanguis/server/weapons/create_function.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/melee.hpp>
#include <sanguis/server/weapons/melee_parameters.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/spawn_weapon.hpp>
#include <sanguis/server/weapons/spider.hpp>
#include <sanguis/server/weapons/spider_parameters.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/factory/parameters.hpp>
#include <sanguis/server/weapons/factory/spider.hpp>
#include <sanguis/server/weapons/modifiers/apply.hpp>
#include <sanguis/server/weapons/modifiers/damage.hpp>
#include <sanguis/server/weapons/modifiers/health.hpp>
#include <sanguis/server/weapons/modifiers/make_guaranteed.hpp>
#include <sanguis/server/weapons/modifiers/make_potential.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>

sanguis::server::weapons::unique_ptr sanguis::server::weapons::factory::spider(
    sanguis::server::weapons::factory::parameters const &_parameters)
{
  sanguis::random_generator &random_generator(_parameters.random_generator());

  sanguis::server::weapons::common_parameters const common_parameters{
      _parameters.common_parameters()};

  sanguis::server::entities::enemies::difficulty const difficulty(_parameters.difficulty());

  sanguis::server::weapons::create_function const spawn_weapon{
      [&random_generator, common_parameters, difficulty]
      {
        return fcppt::unique_ptr_to_base<
            sanguis::server::weapons::weapon>(fcppt::make_unique_ptr<
                                              sanguis::server::weapons::melee>(
            common_parameters,
            sanguis::server::weapons::modifiers::apply(
                random_generator,
                difficulty,
                sanguis::server::weapons::modifiers::make_guaranteed<
                    sanguis::server::weapons::melee_parameters>(
                    sanguis::server::weapons::modifiers::damage{}),
                sanguis::server::weapons::modifiers::make_potential<
                    sanguis::server::weapons::melee_parameters>(),
                sanguis::server::weapons::melee_parameters(
                    sanguis::server::weapons::range(
                        100.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                        ),
                    sanguis::server::weapons::backswing_time(sanguis::duration_second(
                        0.3F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                        )),
                    sanguis::server::weapons::damage{
                        3.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                    },
                    sanguis::server::damage::make_array(
                        {sanguis::server::damage::normal = sanguis::server::damage::full})))));
      }};

  return fcppt::unique_ptr_to_base<
      sanguis::server::weapons::weapon>(fcppt::make_unique_ptr<sanguis::server::weapons::spider>(
      common_parameters,
      sanguis::server::weapons::spawn_weapon(spawn_weapon),
      sanguis::server::weapons::modifiers::apply(
          _parameters.random_generator(),
          _parameters.difficulty(),
          sanguis::server::weapons::modifiers::make_guaranteed<
              sanguis::server::weapons::spider_parameters>(),
          sanguis::server::weapons::modifiers::make_potential<
              sanguis::server::weapons::spider_parameters>(
              sanguis::server::weapons::modifiers::health{}),
          sanguis::server::weapons::spider_parameters(
              sanguis::server::health(
                  100.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  ),
              sanguis::server::weapons::backswing_time(sanguis::duration_second(
                  3.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  )),
              sanguis::server::weapons::cast_point(sanguis::duration_second(
                  0.1F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  )),
              sanguis::server::weapons::range(
                  1000.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  )))));
}
