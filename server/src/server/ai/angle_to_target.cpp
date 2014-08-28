#include <sanguis/server/angle.hpp>
#include <sanguis/server/optional_angle.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/ai/angle_to_target.hpp>
#include <sanguis/server/ai/target.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/vector/distance.hpp>
#include <fcppt/math/vector/signed_angle_between_cast.hpp>


sanguis::server::optional_angle const
sanguis::server::ai::angle_to_target(
	sanguis::server::entities::with_ai &_me,
	sanguis::server::ai::target const _target
)
{
	return
		fcppt::math::vector::distance(
			_target.get().get(),
			_me.center().get()
		)
		<
		fcppt::literal<
			sanguis::server::space_unit
		>(
			1
		)
		?
			sanguis::server::optional_angle()
		:
			sanguis::server::optional_angle(
				sanguis::server::angle(
					fcppt::math::vector::signed_angle_between_cast<
						sanguis::server::space_unit
					>(
						_me.center().get(),
						_target.get().get()
					)
				)
			)
		;
}
