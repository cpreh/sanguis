#ifndef SANGUIS_SERVER_ENTITIES_WITH_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_HEALTH_HPP_INCLUDED

#include <sanguis/diff_timer.hpp>
#include <sanguis/server/health_fwd.hpp>
#include <sanguis/server/regeneration_fwd.hpp>
#include <sanguis/server/damage/armor_array.hpp>
#include <sanguis/server/damage/modified_array_fwd.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/server/entities/ifaces/with_health.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <sanguis/server/entities/ifaces/with_links.hpp>
#include <sanguis/server/entities/property/always_max.hpp>
#include <sanguis/server/entities/property/changeable.hpp>
#include <sanguis/server/net/health.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/signal/auto_connection.hpp>

namespace sanguis::server::entities
{

class with_health : public virtual sanguis::server::entities::base,
                    public virtual sanguis::server::entities::ifaces::with_health,
                    public virtual sanguis::server::entities::ifaces::with_id,
                    public virtual sanguis::server::entities::ifaces::with_links
{
  FCPPT_NONMOVABLE(with_health);

public:
  void damage(sanguis::server::damage::unit, sanguis::server::damage::modified_array const &);

  void kill() override;

  [[nodiscard]] sanguis::server::entities::property::changeable &health() override;

  [[nodiscard]] sanguis::server::entities::property::always_max &regeneration();

  [[nodiscard]] sanguis::server::health current_health() const override;

  [[nodiscard]] sanguis::server::health max_health() const override;

  [[nodiscard]] sanguis::server::damage::armor_array const &armor() const;

  ~with_health() override;

protected:
  with_health(
      sanguis::server::health,
      sanguis::server::regeneration,
      sanguis::server::damage::armor_array const &);

  void update() override;

private:
  [[nodiscard]] bool dead() const override;

  void health_change();

  void max_health_change();

  sanguis::server::damage::armor_array armor_;

  sanguis::server::entities::property::changeable health_;

  sanguis::server::entities::property::always_max regeneration_;

  sanguis::diff_timer regeneration_timer_;

  sanguis::server::net::health net_health_;

  fcppt::signal::auto_connection const health_change_;

  fcppt::signal::auto_connection const max_health_change_;
};

}

#endif
