#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/enemies/attribute.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/normal.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/skills/mother_spider.hpp>
#include <sanguis/server/entities/enemies/skills/skill.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/copy.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/repeat.hpp>
#include <fcppt/optional/maybe_void_multi.hpp>

sanguis::server::entities::enemies::skills::mother_spider::mother_spider() = default;

sanguis::server::entities::enemies::skills::mother_spider::~mother_spider() = default;

void sanguis::server::entities::enemies::skills::mother_spider::on_die(
    sanguis::server::entities::enemies::enemy const &_enemy)
{
  fcppt::optional::maybe_void_multi(
      [&_enemy](
          fcppt::reference<sanguis::server::weapons::weapon const> const _primary_weapon,
          fcppt::reference<sanguis::server::environment::object> const _environment)
      {
        // TODO(philipp): Make copies of enemies smaller
        fcppt::algorithm::repeat(
            1U,
            [&_enemy, &_primary_weapon, &_environment]
            {
              sanguis::server::environment::insert_no_result(
                  _environment.get(),
                  fcppt::unique_ptr_to_base<
                      sanguis::server::entities::
                          with_id>(fcppt::make_unique_ptr<
                                   sanguis::server::entities::enemies::
                                       normal>(sanguis::server::entities::enemies::parameters{
                      _enemy.enemy_type(),
                      _environment
                          ->load_context(),
                      _enemy.armor(),
                      _enemy.mass(),
                      // TODO(philipp): This parameter should probably be of type max_health
                      sanguis::server::health{
                          _enemy.max_health().get() /
                          4.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                      },
                      _enemy.max_movement_speed(),
                      fcppt::copy(_enemy.create_ai()),
                      _primary_weapon->clone(),
                      sanguis::server::pickup_probability{0.F},
                      sanguis::server::exp{
                          _enemy.exp().get() /
                          4.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                      },
                      _enemy.difficulty(),
                      sanguis::server::entities::spawn_owner(
                          sanguis::server::entities::auto_weak_link{}),
                      sanguis::server::auras::container{}})),
                  sanguis::server::entities::insert_parameters_center(_enemy.center()));
            });
      },
      _enemy.primary_weapon(),
      _enemy.environment());
}

sanguis::server::entities::enemies::attribute
sanguis::server::entities::enemies::skills::mother_spider::attribute() const
{
  return sanguis::server::entities::enemies::attribute(FCPPT_TEXT("mother spider"));
}
