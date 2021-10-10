#ifndef SANGUIS_SERVER_ENTITIES_EXP_AREA_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_EXP_AREA_HPP_INCLUDED

#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_base_ref.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/collision/ghost_base.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/center_ghost.hpp>
#include <sanguis/server/entities/player_fwd.hpp>
#include <sanguis/server/entities/simple.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_comparison.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_std_hash.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool_fwd.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::entities
{

class exp_area : public virtual sanguis::server::entities::with_ghosts,
                 public sanguis::server::entities::simple,
                 private sanguis::server::collision::ghost_base,
                 private sanguis::server::entities::center_ghost
{
  FCPPT_NONMOVABLE(exp_area);

public:
  explicit exp_area(sanguis::server::exp);

  ~exp_area() override;

private:
  void remove_from_game() override;

  [[nodiscard]] bool dead() const override;

  [[nodiscard]] boost::logic::tribool
  can_collide_with(sanguis::collision::world::body_base const &) const override;

  void on_body_enter(
      sanguis::collision::world::body_base_ref, sanguis::collision::world::created) override;

  void on_body_exit(sanguis::collision::world::body_base &) override;

  sanguis::server::exp const exp_;

  using weak_link_map = std::unordered_map<
      fcppt::reference<sanguis::server::entities::player>,
      sanguis::server::entities::auto_weak_link>;

  weak_link_map player_links_;
};

}

#endif
