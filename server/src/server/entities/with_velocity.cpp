#include <sanguis/collision/speed.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/optional_mass_fwd.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/collision/from_speed.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/movement_speed_initial.hpp>
#include <sanguis/server/entities/optional_transfer_result.hpp>
#include <sanguis/server/entities/speed_to_abs.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/property/change_callback.hpp>
#include <sanguis/server/entities/property/change_event_fwd.hpp>
#include <sanguis/server/entities/property/changeable.hpp>
#include <sanguis/server/environment/object.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::server::entities::with_velocity::with_velocity(
    sanguis::server::radius const _radius,
    sanguis::server::optional_mass const &_mass,
    sanguis::server::entities::movement_speed_initial const _movement_speed,
    sanguis::server::direction const _direction)
    : sanguis::server::entities::with_body(_radius, _mass),
      movement_speed_(_movement_speed.get()),
      direction_(_direction),
      net_speed_(fcppt::make_cref(this->diff_clock())),
      speed_change_(movement_speed_.register_change_callback(
          sanguis::server::entities::property::change_callback{
              [this](sanguis::server::entities::property::change_event const &)
              { this->desired_speed_change(); }}))
{
}

FCPPT_PP_POP_WARNING

void sanguis::server::entities::with_velocity::update()
{
  sanguis::server::entities::with_body::update();

  if (net_speed_.update())
  {
    fcppt::optional::maybe_void(
        this->environment(),
        [this](fcppt::reference<sanguis::server::environment::object> const _environment)
        { _environment->speed_changed(this->id(), this->speed()); });
  }
}

sanguis::server::entities::optional_transfer_result
sanguis::server::entities::with_velocity::on_transfer(
    sanguis::server::entities::transfer_parameters const &_parameters)
{
  net_speed_.reset();

  return sanguis::server::entities::with_body::on_transfer(_parameters);
}

sanguis::server::entities::with_velocity::~with_velocity() = default;

sanguis::server::entities::property::changeable &
sanguis::server::entities::with_velocity::movement_speed()
{
  return movement_speed_;
}

sanguis::server::entities::movement_speed
sanguis::server::entities::with_velocity::max_movement_speed() const
{
  return sanguis::server::entities::movement_speed{movement_speed_.max()};
}

sanguis::server::direction sanguis::server::entities::with_velocity::direction() const
{
  return direction_;
}

void sanguis::server::entities::with_velocity::direction(
    sanguis::server::direction const _direction)
{
  direction_ = _direction;

  this->desired_speed_change();
}

sanguis::server::speed sanguis::server::entities::with_velocity::speed() const
{
  return this->body_speed();
}

void sanguis::server::entities::with_velocity::desired_speed_change()
{
  sanguis::server::speed const cur_speed(this->desired_speed());

  this->body_speed(cur_speed);

  net_speed_.set(cur_speed);
}

void sanguis::server::entities::with_velocity::speed_changed(
    sanguis::collision::speed const &_speed)
{
  net_speed_.set(sanguis::server::collision::from_speed(_speed));
}

sanguis::server::speed sanguis::server::entities::with_velocity::desired_speed() const
{
  return sanguis::server::entities::speed_to_abs(this->direction(), movement_speed_.current());
}

sanguis::server::speed sanguis::server::entities::with_velocity::initial_speed() const
{
  return this->desired_speed();
}
