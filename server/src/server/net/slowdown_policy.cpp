#include <sanguis/clock.hpp>
#include <sanguis/slowdown.hpp>
#include <sanguis/server/net/slowdown_policy.hpp>
#include <fcppt/math/diff.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


sanguis::clock::duration
sanguis::server::net::slowdown_policy::start_duration()
{
	return
		std::chrono::seconds(
			10
		);
}

sanguis::clock::duration
sanguis::server::net::slowdown_policy::difference(
	sanguis::slowdown const _slowdown1,
	sanguis::slowdown const _slowdown2
)
{
	// TODO: What do we want to use here?
	return
		std::chrono::duration_cast<
			sanguis::clock::duration
		>(
			fcppt::math::diff(
				_slowdown1.get(),
				_slowdown2.get()
			)
			*
			std::chrono::seconds(
				5
			)
		);
}
