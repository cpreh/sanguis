#include <sanguis/duration.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/net/health_policy.hpp>
#include <fcppt/math/diff.hpp>


sanguis::duration const
sanguis::server::net::health_policy::start_duration()
{
	return
		sanguis::duration_second(
			2.f
		);
}

sanguis::duration const
sanguis::server::net::health_policy::difference(
	sanguis::server::health const _health1,
	sanguis::server::health const _health2
)
{
	return
		// TODO!
		sanguis::duration_second(
			fcppt::math::diff(
				_health1.get(),
				_health2.get()
			)
		);
}
