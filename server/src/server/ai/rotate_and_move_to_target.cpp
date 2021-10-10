#include <sanguis/server/angle.hpp>
#include <sanguis/server/optional_angle.hpp>
#include <sanguis/server/ai/angle_to_target.hpp>
#include <sanguis/server/ai/move_to_target.hpp>
#include <sanguis/server/ai/rotate_and_move_to_target.hpp>
#include <sanguis/server/ai/rotate_to.hpp>
#include <sanguis/server/ai/speed_factor.hpp>
#include <sanguis/server/ai/target.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <fcppt/optional/maybe_void.hpp>

void sanguis::server::ai::rotate_and_move_to_target(
    sanguis::server::entities::with_ai &_me,
    sanguis::server::ai::target const &_target,
    sanguis::server::ai::speed_factor const _speed_factor)
{
  sanguis::server::optional_angle const angle(sanguis::server::ai::angle_to_target(_me, _target));

  fcppt::optional::maybe_void(
      angle,
      [&_me](sanguis::server::angle const _angle_to_target)
      { sanguis::server::ai::rotate_to(_me, _angle_to_target); });

  sanguis::server::ai::move_to_target(_me, angle, _target, _speed_factor);
}
