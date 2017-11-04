#include <sanguis/server/angle.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/optional_angle.hpp>
#include <sanguis/server/ai/angle_to_target.hpp>
#include <sanguis/server/ai/target.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <fcppt/math/vector/signed_angle_between.hpp>
#include <fcppt/optional/map.hpp>


sanguis::server::optional_angle
sanguis::server::ai::angle_to_target(
	sanguis::server::entities::with_ai &_me,
	sanguis::server::ai::target const _target
)
{
	return
		fcppt::optional::map(
			fcppt::math::vector::signed_angle_between(
				_me.center().get(),
				_target.get().get()
			),
			[](
				sanguis::server::space_unit const _angle
			)
			{
				return
					sanguis::server::angle(
						_angle
					);
			}
		);
}
