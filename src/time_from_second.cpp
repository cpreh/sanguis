#include "time_from_second.hpp"
#include <fcppt/chrono/duration_cast.hpp>
#include <fcppt/chrono/duration_impl.hpp>

sanguis::time_delta const
sanguis::time_from_second(
	sanguis::time_unit const _time
)
{
	return
		fcppt::chrono::duration_cast<
			sanguis::time_delta
		>(
			fcppt::chrono::duration<
				sanguis::time_unit
			>(
				_time
			)
		);
}
