#include <sanguis/pickup_type.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/pickups/health.hpp>
#include <sanguis/server/entities/pickups/pickup.hpp>
#include <sanguis/server/entities/property/add.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <fcppt/const.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/optional/maybe.hpp>

sanguis::server::entities::pickups::health::health(
    sanguis::server::environment::load_context &_load_context,
    sanguis::server::team const _team,
    sanguis::server::health const _amount)
    : sanguis::server::entities::pickups::pickup(
          sanguis::pickup_type::health, _load_context, _team),
      amount_(_amount)
{
}

sanguis::server::entities::pickups::health::~health() = default;

bool sanguis::server::entities::pickups::health::do_pickup(
    sanguis::server::entities::base &_receiver)
{
  return fcppt::optional::maybe(
      fcppt::cast::dynamic<sanguis::server::entities::with_health>(_receiver),
      fcppt::const_(false),
      [this](fcppt::reference<sanguis::server::entities::with_health> const _with_health)
      {
        sanguis::server::entities::property::add(_with_health.get().health(), amount_.get());

        return true;
      });
}
