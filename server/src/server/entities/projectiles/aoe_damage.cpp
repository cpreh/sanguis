#include <sanguis/server/aoe.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/aoe_damage.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/damage/modified_array_fwd.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/center_ghost.hpp>
#include <sanguis/server/entities/simple.hpp>
#include <sanguis/server/entities/with_auras.hpp>
#include <sanguis/server/entities/projectiles/aoe_damage.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/container/make.hpp>

sanguis::server::entities::projectiles::aoe_damage::aoe_damage(
    sanguis::server::team const _team,
    sanguis::server::aoe const _aoe,
    sanguis::server::damage::unit const _damage,
    sanguis::server::damage::modified_array const &_damage_values)
    : sanguis::server::entities::with_auras(
          fcppt::container::make<sanguis::server::auras::container>(
              fcppt::unique_ptr_to_base<sanguis::server::auras::aura>(
                  fcppt::make_unique_ptr<sanguis::server::auras::aoe_damage>(
                      _team,
                      _aoe,
                      sanguis::server::auras::influence::debuff,
                      _damage,
                      _damage_values)))),
      sanguis::server::entities::simple(),
      sanguis::server::entities::center_ghost()
{
}

sanguis::server::entities::projectiles::aoe_damage::~aoe_damage() = default;

bool sanguis::server::entities::projectiles::aoe_damage::dead() const { return true; }
