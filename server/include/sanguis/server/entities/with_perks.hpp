#ifndef SANGUIS_SERVER_ENTITIES_WITH_PERKS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_PERKS_HPP_INCLUDED

#include <sanguis/perk_type_fwd.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_perks_fwd.hpp>
#include <sanguis/server/entities/ifaces/with_health.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/entities/ifaces/with_velocity.hpp>
#include <sanguis/server/entities/ifaces/with_weapon.hpp>
#include <sanguis/server/perks/unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::entities
{

class with_perks : public virtual sanguis::server::entities::base,
                   public virtual sanguis::server::entities::ifaces::with_health,
                   public virtual sanguis::server::entities::ifaces::with_velocity,
                   public virtual sanguis::server::entities::ifaces::with_weapon,
                   public virtual sanguis::server::entities::ifaces::with_team
{
  FCPPT_NONMOVABLE(with_perks);

public:
  void add_perk(sanguis::perk_type);

  ~with_perks() override;

protected:
  explicit with_perks(sanguis::random_generator_ref);

  void update() override;

private:
  using perk_container = std::map<sanguis::perk_type, sanguis::server::perks::unique_ptr>;

  sanguis::random_generator_ref const random_generator_;

  perk_container perks_;
};

}

#endif
