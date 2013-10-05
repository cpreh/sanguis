#include <sanguis/duration.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/net/center_policy.hpp>
#include <fcppt/math/vector/distance.hpp>


sanguis::duration const
sanguis::server::net::center_policy::start_duration()
{
	return
		sanguis::duration_second(
			0.5f
		);
}

sanguis::duration const
sanguis::server::net::center_policy::difference(
	sanguis::server::center const _center1,
	sanguis::server::center const _center2
)
{
	return
		// TODO!
		sanguis::duration_second(
			fcppt::math::vector::distance(
				_center1.get(),
				_center2.get()
			)
		);
}
