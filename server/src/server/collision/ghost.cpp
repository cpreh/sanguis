#include <sanguis/exception.hpp>
#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/collision/world/body_exit_container.hpp>
#include <sanguis/collision/world/ghost.hpp>
#include <sanguis/collision/world/ghost_base_ref.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <sanguis/collision/world/ghost_parameters.hpp>
#include <sanguis/collision/world/ghost_unique_ptr.hpp>
#include <sanguis/collision/world/object.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/collision/ghost.hpp>
#include <sanguis/server/collision/to_center.hpp>
#include <sanguis/server/collision/to_radius.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/assign.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/to_exception.hpp>

sanguis::server::collision::ghost::ghost(
    sanguis::collision::world::ghost_base_ref const _ghost_base,
    sanguis::collision::world::ghost_group const _collision_group,
    sanguis::server::radius const _radius)
    : ghost_base_(_ghost_base), collision_group_(_collision_group), radius_(_radius), impl_()
{
}

sanguis::server::collision::ghost::ghost(ghost &&) noexcept = default;

sanguis::server::collision::ghost &
sanguis::server::collision::ghost::operator=(ghost &&) noexcept = default;

sanguis::server::collision::ghost::~ghost() = default;

sanguis::collision::world::body_enter_container sanguis::server::collision::ghost::transfer(
    sanguis::collision::world::object &_world, sanguis::server::center const &_center)
{
  if (impl_.has_value())
  {
    throw sanguis::exception{
        FCPPT_TEXT("server::collision::ghost::transfer called, but impl_ is already set")};
  }

  sanguis::collision::world::ghost_unique_ptr const &new_ghost(fcppt::optional::assign(
      impl_,
      _world.create_ghost(sanguis::collision::world::ghost_parameters(
          sanguis::server::collision::to_center(_center),
          sanguis::server::collision::to_radius(radius_),
          collision_group_,
          ghost_base_))));

  return _world.activate_ghost(fcppt::make_ref(*new_ghost));
}

sanguis::collision::world::body_exit_container
sanguis::server::collision::ghost::destroy(sanguis::collision::world::object &_world)
{
  sanguis::collision::world::body_exit_container result{
      _world.deactivate_ghost(fcppt::make_ref(this->ghost_exn()))};

  impl_ = optional_ghost_unique_ptr();

  return result;
}

void sanguis::server::collision::ghost::center(sanguis::server::center const &_center)
{
  this->ghost_exn().center(sanguis::server::collision::to_center(_center));
}

sanguis::collision::world::ghost& sanguis::server::collision::ghost::ghost_exn() const
{
  return *fcppt::optional::to_exception(
      this->impl_, [] { return sanguis::exception{FCPPT_TEXT("Ghost not set!")}; });
}
