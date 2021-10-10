#include <sanguis/duration_second.hpp>
#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/common_parameters.hpp>
#include <sanguis/server/weapons/create_function.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/pistol.hpp>
#include <sanguis/server/weapons/pistol_parameters.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/sentry.hpp>
#include <sanguis/server/weapons/sentry_parameters.hpp>
#include <sanguis/server/weapons/spawn_weapon.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/factory/parameters.hpp>
#include <sanguis/server/weapons/factory/sentry.hpp>
#include <sanguis/server/weapons/modifiers/apply.hpp>
#include <sanguis/server/weapons/modifiers/damage.hpp>
#include <sanguis/server/weapons/modifiers/health.hpp>
#include <sanguis/server/weapons/modifiers/make_guaranteed.hpp>
#include <sanguis/server/weapons/modifiers/make_potential.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>

sanguis::server::weapons::unique_ptr sanguis::server::weapons::factory::sentry(
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
                                              sanguis::server::weapons::pistol>(
            common_parameters,
            sanguis::weapon_type(sanguis::primary_weapon_type::pistol),
            sanguis::server::weapons::modifiers::apply(
                random_generator,
                difficulty,
                sanguis::server::weapons::modifiers::make_guaranteed<
                    sanguis::server::weapons::pistol_parameters>(
                    sanguis::server::weapons::modifiers::damage{}),
                sanguis::server::weapons::modifiers::make_potential<
                    sanguis::server::weapons::pistol_parameters>(),
                sanguis::server::weapons::pistol_parameters(
                    sanguis::server::weapons::accuracy(
                        0.95F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                        ),
                    sanguis::server::weapons::backswing_time(sanguis::duration_second(
                        0.06F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                        )),
                    sanguis::server::weapons::damage(
                        2.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                        ),
                    sanguis::server::weapons::cast_point(sanguis::duration_second(
                        0.2F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                        )),
                    sanguis::server::weapons::magazine_size(
                        20U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                        ),
                    sanguis::server::weapons::reload_time(sanguis::duration_second(
                        5.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                        )),
                    sanguis::server::weapons::range(
                        1000.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                        )))));
      }};

  return fcppt::unique_ptr_to_base<
      sanguis::server::weapons::weapon>(fcppt::make_unique_ptr<sanguis::server::weapons::sentry>(
      _parameters.common_parameters(),
      sanguis::server::weapons::spawn_weapon(spawn_weapon),
      sanguis::server::weapons::modifiers::apply(
          _parameters.random_generator(),
          _parameters.difficulty(),
          sanguis::server::weapons::modifiers::make_guaranteed<
              sanguis::server::weapons::sentry_parameters>(),
          sanguis::server::weapons::modifiers::make_potential<
              sanguis::server::weapons::sentry_parameters>(
              sanguis::server::weapons::modifiers::health{}),
          sanguis::server::weapons::sentry_parameters(
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
