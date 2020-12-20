#include <sanguis/duration.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/net/center_policy.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/vector/distance.hpp>


sanguis::duration
sanguis::server::net::center_policy::start_duration()
{
	return
		sanguis::duration_second(
			0.5F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		);
}

sanguis::duration
sanguis::server::net::center_policy::difference(
	sanguis::server::center const &_center1,
	sanguis::server::center const &_center2
)
{
	return
		sanguis::duration_second(
			fcppt::math::vector::distance(
				_center1.get(),
				_center2.get()
			)
			/
			fcppt::literal<
				sanguis::server::space_unit
			>(
				20 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			)
		);
}
