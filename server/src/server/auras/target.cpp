#include <sanguis/optional_aura_type.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/server/add_target_callback.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/remove_target_callback.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/collision_group.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/auras/target.hpp>
#include <sanguis/server/auras/target_kind.hpp>
#include <sanguis/server/auras/target_kind_to_influence.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <sanguis/server/entities/with_body_ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::server::auras::target::target(
    sanguis::server::radius const _radius,
    sanguis::server::team const _team,
    sanguis::server::auras::target_kind const _kind,
    sanguis::server::add_target_callback &&_add_target,
    sanguis::server::remove_target_callback &&_remove_target)
    : sanguis::server::auras::aura(
          _radius,
          sanguis::server::auras::collision_group(
              _team, sanguis::server::auras::target_kind_to_influence(_kind))),
      add_target_(std::move(_add_target)),
      remove_target_(std::move(_remove_target))
{
}

sanguis::server::auras::target::~target() = default;

sanguis::optional_aura_type sanguis::server::auras::target::type() const
{
  return sanguis::optional_aura_type();
}

void sanguis::server::auras::target::enter(
    sanguis::server::entities::with_body_ref const _target, sanguis::collision::world::created)
{
  this->add_target_(_target);
}

void sanguis::server::auras::target::leave(sanguis::server::entities::with_body &_target)
{
  this->remove_target_(_target);
}
