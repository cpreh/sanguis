#include <sanguis/diff_timer.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/spawns/count_per_wave.hpp>
#include <sanguis/server/entities/spawns/interval.hpp>
#include <sanguis/server/entities/spawns/limit.hpp>
#include <sanguis/server/entities/spawns/limited.hpp>
#include <sanguis/server/entities/spawns/size_type.hpp>
#include <sanguis/server/entities/spawns/spawn.hpp>
#include <sanguis/server/entities/spawns/total_count.hpp>
#include <sanguis/server/weapons/common_parameters_fwd.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::server::entities::spawns::limited::limited(
    sanguis::random_generator_ref const _random_generator,
    sanguis::server::weapons::common_parameters const &_weapons_parameters,
    sanguis::creator::enemy_type const _enemy_type,
    sanguis::creator::enemy_kind const _enemy_kind,
    sanguis::server::world::difficulty const _difficulty,
    sanguis::server::entities::spawns::count_per_wave const _count_per_wave,
    sanguis::server::entities::spawns::interval const _interval,
    sanguis::server::entities::spawns::limit const _limit,
    sanguis::server::entities::spawns::total_count const _total_count)
    : sanguis::server::entities::spawns::spawn(
          _random_generator, _weapons_parameters, _enemy_type, _enemy_kind, _difficulty),
      count_per_wave_(_count_per_wave),
      delay_timer_(
          sanguis::diff_timer::parameters(fcppt::make_cref(this->diff_clock()), _interval.get())),
      alive_(0U),
      spawned_(0U),
      limit_(_limit),
      total_count_(_total_count)
{
  if (_limit.get() == 0U)
  {
    throw sanguis::exception{FCPPT_TEXT("spawns::limited: limit cannot be 0")};
  }

  if (_count_per_wave.get() == 0U)
  {
    throw sanguis::exception{FCPPT_TEXT("spawns::limited: count_per_wave cannot be 0")};
  }
}

FCPPT_PP_POP_WARNING

sanguis::server::entities::spawns::limited::~limited() = default;

bool sanguis::server::entities::spawns::limited::dead() const
{
  return spawned_ == total_count_.get();
}

void sanguis::server::entities::spawns::limited::unregister(sanguis::server::entities::base &)
{
  if (alive_ == 0U)
  {
    throw sanguis::exception{FCPPT_TEXT("spawns::limited::unregister: alive == 0")};
  }

  --alive_;
}

sanguis::server::entities::spawns::size_type sanguis::server::entities::spawns::limited::may_spawn()
{
  return sge::timer::reset_when_expired(fcppt::make_ref(delay_timer_))
             ? std::min(limit_.get() - alive_, count_per_wave_.get())
             : 0U;
}

void sanguis::server::entities::spawns::limited::add_count(
    sanguis::server::entities::spawns::size_type const _add)
{
  alive_ += _add;

  spawned_ += _add;
}
