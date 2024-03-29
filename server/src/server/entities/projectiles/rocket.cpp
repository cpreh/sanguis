#include <sanguis/aoe_projectile_type.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/server/aoe.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/damage/modified_array.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/simple.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/server/entities/projectiles/aoe_damage.hpp>
#include <sanguis/server/entities/projectiles/aoe_projectile.hpp>
#include <sanguis/server/entities/projectiles/life_time.hpp>
#include <sanguis/server/entities/projectiles/rocket.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/optional/maybe_void.hpp>

sanguis::server::entities::projectiles::rocket::rocket(
    sanguis::server::environment::load_context &_load_context,
    sanguis::server::team const _team,
    sanguis::server::damage::unit const _damage,
    sanguis::server::damage::modified_array const &_damage_modifiers,
    sanguis::server::aoe const _aoe,
    sanguis::server::direction const _direction)
    : sanguis::server::entities::projectiles::aoe_projectile(
          sanguis::aoe_projectile_type::rocket,
          _team,
          sanguis::server::entities::movement_speed(
              300.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              ),
          _load_context,
          sanguis::server::entities::projectiles::life_time(sanguis::duration_second(
              10.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              )),
          _aoe,
          _direction),
      damage_(_damage),
      damage_modifiers_(_damage_modifiers)
{
}

sanguis::server::entities::projectiles::rocket::~rocket() = default;

void sanguis::server::entities::projectiles::rocket::do_damage(
    sanguis::server::entities::with_health &)
{
  this->expire();
}

void sanguis::server::entities::projectiles::rocket::remove_from_game()
{
  fcppt::optional::maybe_void(
      this->environment(),
      [this](fcppt::reference<sanguis::server::environment::object> const _environment)
      {
        sanguis::server::environment::insert_no_result(
            _environment.get(),
            fcppt::unique_ptr_to_base<sanguis::server::entities::simple>(
                fcppt::make_unique_ptr<sanguis::server::entities::projectiles::aoe_damage>(
                    this->team(), this->aoe(), this->damage_, this->damage_modifiers_)),
            sanguis::server::entities::insert_parameters_center(this->center()));
      });
}
