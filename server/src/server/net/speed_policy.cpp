#include <sanguis/duration.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/net/speed_policy.hpp>
#include <fcppt/math/vector/distance.hpp>


sanguis::duration
sanguis::server::net::speed_policy::start_duration()
{
	return
		sanguis::duration_second(
			0.5F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		);
}

sanguis::duration
sanguis::server::net::speed_policy::difference(
	sanguis::server::speed const &_speed1,
	sanguis::server::speed const &_speed2
)
{
	return
		sanguis::duration_second(
			fcppt::math::vector::distance(
				_speed1.get(),
				_speed2.get()
			)
		);
}
