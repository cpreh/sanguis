#include <sanguis/aura_type.hpp>
#include <sanguis/optional_aura_type.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/buff.hpp>
#include <sanguis/server/auras/collision_group.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/buffs/buff.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/buffs/create_callback.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_body_ref.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/cast/dynamic_cross.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::server::auras::buff::buff(
    sanguis::server::radius const _radius,
    sanguis::server::team const _team,
    sanguis::aura_type const _aura_type,
    sanguis::server::auras::influence const _influence,
    sanguis::server::buffs::create_callback &&_create_callback)
    : sanguis::server::auras::aura(
          _radius, sanguis::server::auras::collision_group(_team, _influence)),
      aura_type_(_aura_type),
      create_callback_(std::move(_create_callback)),
      provider_()
{
}

sanguis::server::auras::buff::~buff() = default;

sanguis::optional_aura_type sanguis::server::auras::buff::type() const
{
  return sanguis::optional_aura_type(aura_type_);
}

void sanguis::server::auras::buff::enter(
    sanguis::server::entities::with_body_ref const _entity, sanguis::collision::world::created)
{
  fcppt::optional::maybe_void(
      fcppt::cast::dynamic_cross<sanguis::server::entities::with_buffs>(_entity.get()),
      [this](fcppt::reference<sanguis::server::entities::with_buffs> const _with_buffs)
      {
        fcppt::optional::maybe_void(
            this->create_callback_(
                fcppt::reference_to_base<sanguis::server::entities::base>(_with_buffs)),
            [this, _with_buffs](sanguis::server::buffs::unique_ptr &&_new_buff)
            { this->provider_.add(_with_buffs, std::move(_new_buff)); });
      });
}

void sanguis::server::auras::buff::leave(sanguis::server::entities::with_body &_entity)
{
  fcppt::optional::maybe_void(
      fcppt::cast::dynamic_cross<sanguis::server::entities::with_buffs>(_entity),
      [this](fcppt::reference<sanguis::server::entities::with_buffs> const _with_buffs)
      { this->provider_.remove(_with_buffs.get()); });
}
