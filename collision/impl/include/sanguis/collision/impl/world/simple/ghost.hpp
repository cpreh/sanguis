#ifndef SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_GHOST_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_GHOST_HPP_INCLUDED

#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/impl/world/simple/body_fwd.hpp>
#include <sanguis/collision/impl/world/simple/ghost_fwd.hpp> // IWYU pragma: keep
#include <sanguis/collision/impl/world/simple/ghost_remove_callback.hpp>
#include <sanguis/collision/world/body_exit_container.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/collision/world/ghost.hpp>
#include <sanguis/collision/world/ghost_base_fwd.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <sanguis/collision/world/ghost_parameters_fwd.hpp>
#include <sanguis/collision/world/optional_body_enter_fwd.hpp>
#include <sanguis/collision/world/optional_body_exit_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_comparison.hpp> // IWYU pragma: keep
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_std_hash.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>

namespace sanguis::collision::impl::world::simple
{

class ghost : public sanguis::collision::world::ghost
{
  FCPPT_NONMOVABLE(ghost);

public:
  ghost(
      sanguis::collision::world::ghost_parameters const &,
      sanguis::collision::impl::world::simple::ghost_remove_callback &&);

  ~ghost() override;

  void center(sanguis::collision::center) override;

  [[nodiscard]] sanguis::collision::center center() const;

  [[nodiscard]] sanguis::collision::radius radius() const;

  [[nodiscard]] sanguis::collision::world::ghost_group collision_group() const;

  void pre_update_bodies();

  [[nodiscard]] sanguis::collision::world::body_exit_container post_update_bodies();

  [[nodiscard]] sanguis::collision::world::optional_body_enter
  update_near_body(sanguis::collision::impl::world::simple::body const &);

  [[nodiscard]] sanguis::collision::world::optional_body_enter new_body(
      sanguis::collision::impl::world::simple::body const &, sanguis::collision::world::created);

  [[nodiscard]] sanguis::collision::world::optional_body_exit
  remove_body(sanguis::collision::impl::world::simple::body const &);

  void body_destroyed(sanguis::collision::impl::world::simple::body const &);

private:
  sanguis::collision::impl::world::simple::ghost_remove_callback const ghost_remove_callback_;

  sanguis::collision::radius const radius_;

  sanguis::collision::world::ghost_group const collision_group_;

  sanguis::collision::center center_;

  sanguis::collision::world::ghost_base &ghost_base_;

  enum class body_status
  {
    marked_for_deletion,
    normal
  };

  using const_body_ref = fcppt::reference<sanguis::collision::impl::world::simple::body const>;

  using body_map = std::unordered_map<const_body_ref, body_status>;

  body_map bodies_;
};

}

#endif
