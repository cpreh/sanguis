#include <sanguis/exception.hpp>
#include <sanguis/collision/log_fwd.hpp>
#include <sanguis/collision/world/body.hpp>
#include <sanguis/collision/world/body_base_ref.hpp>
#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/collision/world/body_exit_container.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/body_parameters.hpp>
#include <sanguis/collision/world/body_unique_ptr.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/collision/world/object.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/mass.hpp>
#include <sanguis/server/optional_mass.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/collision/body.hpp>
#include <sanguis/server/collision/from_center.hpp>
#include <sanguis/server/collision/from_speed.hpp>
#include <sanguis/server/collision/to_center.hpp>
#include <sanguis/server/collision/to_mass.hpp>
#include <sanguis/server/collision/to_radius.hpp>
#include <sanguis/server/collision/to_speed.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/assign.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/object_impl.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/preprocessor/ignore_dangling_reference.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::server::collision::body::body(
    sanguis::server::radius const _radius,
    sanguis::server::optional_mass _mass,
    sanguis::collision::world::body_base_ref const _body_base)
    : radius_(_radius), mass_(std::move(_mass)), body_base_(_body_base), body_()
{
}

sanguis::server::collision::body::~body() = default;

void sanguis::server::collision::body::center(sanguis::server::center const &_center)
{
  this->body_exn().center(sanguis::server::collision::to_center(_center));
}

sanguis::server::center sanguis::server::collision::body::center() const
{
  return sanguis::server::collision::from_center(this->body_exn().center());
}

void sanguis::server::collision::body::speed(sanguis::server::speed const &_speed)
{
  this->body_exn().speed(sanguis::server::collision::to_speed(_speed));
}

sanguis::server::speed sanguis::server::collision::body::speed() const
{
  return sanguis::server::collision::from_speed(this->body_exn().speed());
}

sanguis::server::radius sanguis::server::collision::body::radius() const { return radius_; }

sanguis::collision::world::body_enter_container sanguis::server::collision::body::transfer(
    sanguis::collision::log const &_log,
    sanguis::collision::world::object &_world,
    sanguis::collision::world::created const _created,
    sanguis::server::center const &_center,
    sanguis::server::speed const &_speed,
    sanguis::collision::world::body_group const _collision_group)
{
  if (body_.has_value())
  {
    throw sanguis::exception{
        FCPPT_TEXT("server::collision::body::transfer called, but body_ is already set")};
  }

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_IGNORE_DANGLING_REFERENCE
  sanguis::collision::world::body_unique_ptr const &new_body{fcppt::optional::assign(
      body_,
      _world.create_body(sanguis::collision::world::body_parameters(
          _log,
          sanguis::server::collision::to_center(_center),
          sanguis::server::collision::to_speed(_speed),
          sanguis::server::collision::to_radius(radius_),
          fcppt::optional::map(
              mass_,
              [](sanguis::server::mass const &_mass)
              { return sanguis::server::collision::to_mass(_mass); }),
          _collision_group,
          body_base_)))};
  FCPPT_PP_POP_WARNING

  return _world.activate_body(fcppt::make_ref(*new_body), _created);
}

sanguis::collision::world::body_exit_container
sanguis::server::collision::body::remove(sanguis::collision::world::object &_world)
{
  sanguis::collision::world::body_exit_container result{
      _world.deactivate_body(fcppt::make_ref(this->body_exn()))};

  this->body_ = optional_body_unique_ptr();

  return result;
}

sanguis::collision::world::body& sanguis::server::collision::body::body_exn() const
{
  return *fcppt::optional::to_exception(
      this->body_, [] { return sanguis::exception{FCPPT_TEXT("Body not set!")}; });
}
