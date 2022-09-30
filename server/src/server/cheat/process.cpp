#include <sanguis/cheat_type.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/perk_type.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/send_available_perks.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/unicast_callback.hpp>
#include <sanguis/server/auras/burn_create.hpp>
#include <sanguis/server/auras/slow_create.hpp>
#include <sanguis/server/buffs/burn.hpp>
#include <sanguis/server/buffs/burn_interval.hpp>
#include <sanguis/server/buffs/define_special.hpp>
#include <sanguis/server/buffs/slow.hpp>
#include <sanguis/server/buffs/slow_factor.hpp>
#include <sanguis/server/cheat/process.hpp>
#include <sanguis/server/cheat/weapon_type.hpp>
#include <sanguis/server/collision/body_enter.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/player.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/pickups/weapon.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/common_parameters_fwd.hpp>
#include <sanguis/server/weapons/create.hpp>
#include <sanguis/server/weapons/monster_spawner.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/enum/make_range.hpp>
#include <fcppt/optional/maybe_void.hpp>

void sanguis::server::cheat::process(
    sanguis::server::entities::player &_player,
    sanguis::cheat_type const _cheat_type,
    sanguis::server::weapons::common_parameters const &_weapon_parameters,
    sanguis::server::unicast_callback const &_unicast_callback)
{
  SANGUIS_SERVER_BUFFS_DEFINE_SPECIAL(player_burn, burn);

  SANGUIS_SERVER_BUFFS_DEFINE_SPECIAL(player_slow, slow);

  fcppt::optional::maybe_void(
      _player.environment(),
      [&_weapon_parameters, &_player, _cheat_type, &_unicast_callback](
          fcppt::reference<sanguis::server::environment::object> const _environment)
      {
        switch (_cheat_type)
        {
        case sanguis::cheat_type::auras:
          sanguis::server::collision::body_enter(fcppt::container::join(
              _player.add_aura(sanguis::server::auras::burn_create<player_burn>(
                  sanguis::server::radius(
                      300.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                      ),
                  sanguis::server::team::players,
                  sanguis::server::buffs::burn_interval(sanguis::duration_second(1.F)),
                  sanguis::server::damage::unit(
                      10.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                      ))),
              _player.add_aura(sanguis::server::auras::slow_create<player_slow>(
                  sanguis::server::radius(
                      300.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                      ),
                  sanguis::server::team::players,
                  sanguis::server::buffs::slow_factor{
                      0.1F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  }))));
          return;
        case sanguis::cheat_type::exp:
          _player.add_exp(sanguis::server::exp(
              100000.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              ));
          return;
        case sanguis::cheat_type::heal:
          _player.health().current(_player.max_health().get());
          return;
        case sanguis::cheat_type::kill:
          _player.kill();
          return;
        case sanguis::cheat_type::monster_spawner:
          sanguis::server::environment::insert_no_result(
              _environment.get(),
              fcppt::unique_ptr_to_base<sanguis::server::entities::with_id>(
                  fcppt::make_unique_ptr<sanguis::server::entities::pickups::weapon>(
                      _environment.get().load_context(),
                      sanguis::server::team::players,
                      fcppt::unique_ptr_to_base<sanguis::server::weapons::weapon>(
                          fcppt::make_unique_ptr<sanguis::server::weapons::monster_spawner>(
                              _weapon_parameters)))),
              sanguis::server::entities::insert_parameters_center(_player.center()));

          return;
        case sanguis::cheat_type::spider:
        case sanguis::cheat_type::sentry:
        case sanguis::cheat_type::grenade:
        case sanguis::cheat_type::shotgun:
        case sanguis::cheat_type::rocket_launcher:
          fcppt::optional::maybe_void(
              sanguis::server::cheat::weapon_type(_cheat_type),
              [&_environment, &_player, &_weapon_parameters](
                  sanguis::weapon_type const &_weapon_type)
              {
                sanguis::server::environment::insert_no_result(
                    _environment.get(),
                    fcppt::unique_ptr_to_base<
                        sanguis::server::entities::
                            with_id>(fcppt::make_unique_ptr<
                                     sanguis::server::entities::pickups::weapon>(
                        _environment.get().load_context(),
                        sanguis::server::team::players,
                        sanguis::server::weapons::create(
                            _weapon_parameters,
                            _weapon_type,
                            sanguis::server::entities::enemies::difficulty(
                                100.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                                )))),
                    sanguis::server::entities::insert_parameters_center(_player.center()));
              });
          return;
        case sanguis::cheat_type::perks:
          for (auto perk : fcppt::enum_::make_range<sanguis::perk_type>())
          {
            while (_player.perk_choosable(perk))
            {
              _player.add_perk(perk);
            }
          }

          sanguis::server::send_available_perks(_player, _unicast_callback);

          return;
        }

        FCPPT_ASSERT_UNREACHABLE;
      });
}
