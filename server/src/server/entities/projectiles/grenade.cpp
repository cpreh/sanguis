#include <sanguis/aoe_projectile_type.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/server/aoe.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/vector.hpp>
#include <sanguis/server/collision/distance_pos_pos.hpp>
#include <sanguis/server/damage/modified_array.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/optional_transfer_result.hpp>
#include <sanguis/server/entities/simple.hpp>
#include <sanguis/server/entities/transfer_parameters.hpp>
#include <sanguis/server/entities/transfer_result.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/projectiles/aoe_damage.hpp>
#include <sanguis/server/entities/projectiles/aoe_projectile.hpp>
#include <sanguis/server/entities/projectiles/grenade.hpp>
#include <sanguis/server/entities/projectiles/life_time.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <chrono>
#include <utility>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::server::entities::projectiles::grenade::grenade(
    sanguis::server::environment::load_context &_load_context,
    sanguis::server::team const _team,
    sanguis::server::damage::unit const _damage,
    sanguis::server::damage::modified_array const &_damage_modifiers,
    sanguis::server::aoe const _aoe,
    sanguis::server::vector const _dest,
    sanguis::server::direction const _direction)
    : sanguis::server::entities::projectiles::aoe_projectile(
          sanguis::aoe_projectile_type::grenade,
          _team,
          sanguis::server::entities::movement_speed(
              500.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              ),
          _load_context,
          sanguis::server::entities::projectiles::life_time(sanguis::duration_second(
              2.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              )),
          _aoe,
          _direction),
      slowdown_timer_(sanguis::diff_timer::parameters(
          fcppt::make_cref(this->diff_clock()),
          std::chrono::milliseconds(
              100 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              ))),
      damage_(_damage),
      damage_modifiers_(_damage_modifiers),
      dest_(_dest)
{
}

FCPPT_PP_POP_WARNING

sanguis::server::entities::projectiles::grenade::~grenade() = default;

sanguis::server::entities::optional_transfer_result
sanguis::server::entities::projectiles::grenade::on_transfer(
    sanguis::server::entities::transfer_parameters const &_parameters)
{
  return fcppt::optional::map(
      sanguis::server::entities::with_velocity::on_transfer(_parameters),
      [&_parameters, this](sanguis::server::entities::transfer_result &&_result)
      {
        // TODO(philipp): Can we put this somewhere else?
        this->movement_speed().current(std::min(
            this->movement_speed().max(),
            sanguis::server::collision::distance_pos_pos(_parameters.center().get(), dest_)));

        return std::move(_result);
      });
}

void sanguis::server::entities::projectiles::grenade::do_damage(
    sanguis::server::entities::with_health &)
{
}

void sanguis::server::entities::projectiles::grenade::update()
{
  if (sge::timer::reset_when_expired(fcppt::make_ref(slowdown_timer_)))
  {
    this->movement_speed().current(
        this->movement_speed().current() *
        0.9F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    );
  }

  sanguis::server::entities::with_velocity::update();
}

void sanguis::server::entities::projectiles::grenade::remove_from_game()
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
