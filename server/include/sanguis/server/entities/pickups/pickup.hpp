#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_PICKUP_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_PICKUP_HPP_INCLUDED

#include <sanguis/diff_timer.hpp>
#include <sanguis/pickup_type.hpp>
#include <sanguis/collision/world/body_group_fwd.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool_fwd.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::entities::pickups
{

class pickup : public virtual sanguis::server::entities::ifaces::with_team,
               public sanguis::server::entities::with_body,
               public sanguis::server::entities::with_id,
               public sanguis::server::entities::with_links
{
  FCPPT_NONMOVABLE(pickup);

public:
  ~pickup() override;

protected:
  pickup(
      sanguis::pickup_type,
      sanguis::server::environment::load_context &, // NOLINT(google-runtime-references)
      sanguis::server::team);

private:
  [[nodiscard]] bool dead() const override;

  [[nodiscard]] sanguis::server::team team() const override;

  [[nodiscard]] boost::logic::tribool
  can_collide_with_body(sanguis::server::entities::with_body const &) const override;

  void
  collision_with_body(sanguis::server::entities::with_body & // NOLINT(google-runtime-references)
                      ) // NOLINT(google-runtime-references)
      override;

  [[nodiscard]] sanguis::collision::world::body_group collision_group() const override;

  [[nodiscard]] virtual bool
  do_pickup(sanguis::server::entities::base &receiver // NOLINT(google-runtime-references)
            ) // NOLINT(google-runtime-references)
      = 0;

  [[nodiscard]] sanguis::messages::server::unique_ptr
      add_message(sanguis::server::player_id, sanguis::collision::world::created) const override;

  sanguis::server::team const team_;

  sanguis::pickup_type const pickup_type_;

  sanguis::diff_timer life_timer_;
};

}

#endif
