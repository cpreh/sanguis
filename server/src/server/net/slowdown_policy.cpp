#include <sanguis/duration.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/slowdown.hpp>
#include <sanguis/server/net/slowdown_policy.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/diff.hpp>


sanguis::duration
sanguis::server::net::slowdown_policy::start_duration()
{
	return
		sanguis::duration_second(
			10.f
		);
}

sanguis::duration
sanguis::server::net::slowdown_policy::difference(
	sanguis::slowdown const _slowdown1,
	sanguis::slowdown const _slowdown2
)
{
	// TODO: What do we want to use here?
	return
		sanguis::duration_second(
			fcppt::math::diff(
				_slowdown1.get(),
				_slowdown2.get()
			)
			*
			fcppt::literal<
				sanguis::slowdown::value_type
			>(
				5
			)
		);
}
