#include <sanguis/diff_timer.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/regeneration.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/damage/armor_array.hpp>
#include <sanguis/server/damage/modified_array.hpp>
#include <sanguis/server/damage/type.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/property/add.hpp>
#include <sanguis/server/entities/property/always_max.hpp>
#include <sanguis/server/entities/property/change_callback.hpp>
#include <sanguis/server/entities/property/change_event_fwd.hpp>
#include <sanguis/server/entities/property/changeable.hpp>
#include <sanguis/server/entities/property/initial_max.hpp>
#include <sanguis/server/entities/property/subtract.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sge/timer/elapsed_fractional_and_reset.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/enum/make_range.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>

void sanguis::server::entities::with_health::damage(
    sanguis::server::damage::unit const _damage,
    sanguis::server::damage::modified_array const &_amounts)
{
  for (auto const index : fcppt::enum_::make_range<sanguis::server::damage::type>())
  {
    sanguis::server::entities::property::subtract(
        health_,
        _damage.get() * _amounts[index].get() *
            (fcppt::literal<sanguis::server::damage::unit::value_type>(1) - armor_[index].get()));
  }
}

void sanguis::server::entities::with_health::kill() { health_.current(0); }

sanguis::server::entities::property::changeable &sanguis::server::entities::with_health::health()
{
  return health_;
}

sanguis::server::entities::property::always_max &
sanguis::server::entities::with_health::regeneration()
{
  return regeneration_;
}

sanguis::server::health sanguis::server::entities::with_health::current_health() const
{
  return sanguis::server::health(health_.current());
}

sanguis::server::health sanguis::server::entities::with_health::max_health() const
{
  return sanguis::server::health(health_.max());
}

sanguis::server::damage::armor_array const &sanguis::server::entities::with_health::armor() const
{
  return armor_;
}

sanguis::server::entities::with_health::~with_health() = default;

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::server::entities::with_health::with_health(
    sanguis::server::health const _max_health,
    sanguis::server::regeneration const _regeneration,
    sanguis::server::damage::armor_array const &_armor)
    : armor_(_armor),
      health_(sanguis::server::entities::property::initial_max(_max_health.get())),
      regeneration_(_regeneration.get()),
      regeneration_timer_(sanguis::diff_timer::parameters(
          fcppt::make_cref(this->diff_clock()), std::chrono::seconds(1))),
      net_health_(fcppt::make_cref(this->diff_clock())),
      health_change_(
          health_.register_change_callback(sanguis::server::entities::property::change_callback{
              [this](sanguis::server::entities::property::change_event const &)
              { this->health_change(); }})),
      max_health_change_(
          health_.register_max_change_callback(sanguis::server::entities::property::change_callback{
              [this](sanguis::server::entities::property::change_event const &)
              { this->max_health_change(); }}))
{
}

FCPPT_PP_POP_WARNING

void sanguis::server::entities::with_health::update()
{
  sanguis::server::entities::property::add(
      health_,
      sge::timer::elapsed_fractional_and_reset<sanguis::server::space_unit>(regeneration_timer_) *
          this->regeneration().current());

  if (net_health_.update())
  {
    fcppt::optional::maybe_void(
        this->environment(),
        [this](fcppt::reference<sanguis::server::environment::object> const _environment)
        { _environment->health_changed(this->id(), this->current_health()); });
  }
}

bool sanguis::server::entities::with_health::dead() const { return health_.current() <= 0; }

void sanguis::server::entities::with_health::health_change()
{
  net_health_.set(this->current_health());
}

void sanguis::server::entities::with_health::max_health_change()
{
  fcppt::optional::maybe_void(
      this->environment(),
      [this](fcppt::reference<sanguis::server::environment::object> const _environment)
      { _environment->max_health_changed(this->id(), this->max_health()); });
}
