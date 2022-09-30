#ifndef SANGUIS_SERVER_COLLISION_BODY_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_BODY_HPP_INCLUDED

#include <sanguis/collision/log_fwd.hpp>
#include <sanguis/collision/world/body_base_ref.hpp>
#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/collision/world/body_exit_container.hpp>
#include <sanguis/collision/world/body_fwd.hpp>
#include <sanguis/collision/world/body_group_fwd.hpp>
#include <sanguis/collision/world/body_unique_ptr.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/collision/world/object_fwd.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/optional_mass.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/collision/body_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/optional/object_decl.hpp>

namespace sanguis::server::collision
{

class body
{
  FCPPT_NONMOVABLE(body);

public:
  body(
      sanguis::server::radius,
      sanguis::server::optional_mass,
      sanguis::collision::world::body_base_ref);

  ~body();

  void center(sanguis::server::center const &);

  [[nodiscard]] sanguis::server::center center() const;

  void speed(sanguis::server::speed const &);

  [[nodiscard]] sanguis::server::speed speed() const;

  [[nodiscard]] sanguis::server::radius radius() const;

  [[nodiscard]] sanguis::collision::world::body_enter_container transfer(
      sanguis::collision::log const &,
      sanguis::collision::world::object &, // NOLINT(google-runtime-references)
      sanguis::collision::world::created,
      sanguis::server::center const &,
      sanguis::server::speed const &,
      sanguis::collision::world::body_group);

  [[nodiscard]] sanguis::collision::world::body_exit_container
  remove(sanguis::collision::world::object & // NOLINT(google-runtime-references)
  ); // NOLINT(google-runtime-references)
private:
  [[nodiscard]] sanguis::collision::world::body& body_exn() const;

  sanguis::server::radius const radius_;

  sanguis::server::optional_mass const mass_;

  sanguis::collision::world::body_base_ref const body_base_;

  using optional_body_unique_ptr =
      fcppt::optional::object<sanguis::collision::world::body_unique_ptr>;

  optional_body_unique_ptr body_;
};

}

#endif
