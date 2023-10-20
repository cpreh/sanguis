#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/aoe.hpp>
#include <sanguis/server/center.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/direction.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/damage/explosive.hpp>
#include <sanguis/server/damage/modified_array.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/modify_damages.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/enemies/attribute.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/skills/cooldown.hpp>
#include <sanguis/server/entities/enemies/skills/scatter.hpp>
#include <sanguis/server/entities/enemies/skills/skill.hpp>
#include <sanguis/server/entities/projectiles/rocket.hpp>
#include <sanguis/server/entities/projectiles/scatter.hpp>
#include <sanguis/server/entities/projectiles/scatter_create.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/repeat.hpp>
#include <fcppt/optional/maybe_void.hpp>

sanguis::server::entities::enemies::skills::scatter::scatter(
    sanguis::diff_clock_cref const _diff_clock,
    sanguis::random_generator_ref const _random_generator,
    sanguis::server::entities::enemies::skills::cooldown const _cooldown)
    : sanguis::server::entities::enemies::skills::skill(),
      random_generator_(_random_generator),
      cooldown_timer_(sanguis::diff_timer::parameters(_diff_clock, _cooldown.get()))
{
}

sanguis::server::entities::enemies::skills::scatter::~scatter() = default;

void sanguis::server::entities::enemies::skills::scatter::update(
    sanguis::server::entities::enemies::enemy &_entity)
{
  if (!sge::timer::reset_when_expired(fcppt::make_ref(cooldown_timer_)))
  {
    return;
  }

  fcppt::optional::maybe_void(
      _entity.environment(),
      [this, &_entity](fcppt::reference<sanguis::server::environment::object> const _environment)
      {
        fcppt::algorithm::repeat(
            5, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
            [this, &_entity, _environment]
            {
              sanguis::server::damage::modified_array const damage_modifiers(
                  sanguis::server::entities::modify_damages(
                      _entity, sanguis::server::damage::explosive()));

              sanguis::server::environment::insert_no_result(
                  _environment.get(),
                  fcppt::unique_ptr_to_base<
                      sanguis::server::entities::
                          with_id>(fcppt::make_unique_ptr<
                                   sanguis::server::entities::projectiles::scatter>(
                      random_generator_,
                      _environment.get().load_context(),
                      _entity.team(),
                      sanguis::server::direction(_entity.angle().get()),
                      sanguis::server::entities::projectiles::scatter_create(
                          [damage_modifiers](
                              sanguis::server::environment::object &_env,
                              sanguis::server::team const _team,
                              sanguis::server::angle const _angle)
                          {
                            return fcppt::unique_ptr_to_base<
                                sanguis::server::entities::
                                    with_id>(fcppt::make_unique_ptr<
                                             sanguis::server::entities::projectiles::rocket>(
                                _env.load_context(),
                                _team,
                                sanguis::server::damage::unit(
                                    10.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                                    ),
                                damage_modifiers,
                                sanguis::server::aoe(
                                    100.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                                    ),
                                sanguis::server::direction(_angle.get())));
                          }))),
                  sanguis::server::entities::insert_parameters(_entity.center(), _entity.angle()));
            });
      });
}

sanguis::server::entities::enemies::attribute
sanguis::server::entities::enemies::skills::scatter::attribute() const
{
  return sanguis::server::entities::enemies::attribute(FCPPT_TEXT("scattering"));
}
