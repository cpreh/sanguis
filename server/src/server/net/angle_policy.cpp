#include <sanguis/duration.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/net/angle_policy.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/diff.hpp>


sanguis::duration
sanguis::server::net::angle_policy::start_duration()
{
	return
		sanguis::duration_second(
			2.f
		);
}

sanguis::duration
sanguis::server::net::angle_policy::difference(
	sanguis::server::angle const _angle1,
	sanguis::server::angle const _angle2
)
{
	return
		sanguis::duration_second(
			fcppt::math::diff(
				_angle1.get(),
				_angle2.get()
			)
			*
			fcppt::literal<
				sanguis::server::space_unit
			>(
				5
			)
		);
}
