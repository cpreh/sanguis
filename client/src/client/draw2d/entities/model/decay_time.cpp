#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/client/draw2d/entities/model/decay_time.hpp>

sanguis::client::draw2d::entities::model::decay_time::decay_time(
    sanguis::diff_clock_cref const _diff_clock, sanguis::duration const &_duration)
    : timer_(sanguis::diff_timer::parameters(_diff_clock, _duration))
{
}

sanguis::client::draw2d::entities::model::decay_time::decay_time(decay_time &&) noexcept = default;

sanguis::client::draw2d::entities::model::decay_time &
sanguis::client::draw2d::entities::model::decay_time::operator=(decay_time &&) noexcept = default;

sanguis::client::draw2d::entities::model::decay_time::~decay_time() = default;

bool sanguis::client::draw2d::entities::model::decay_time::ended() const
{
  return timer_.expired();
}
