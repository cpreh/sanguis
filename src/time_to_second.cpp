#include "time_to_second.hpp"
#include <fcppt/chrono/duration_cast.hpp>
#include <fcppt/chrono/duration_impl.hpp>

sanguis::time_unit
sanguis::time_to_second(
	sanguis::time_delta const &_time
)
{
	return
		fcppt::chrono::duration_cast<
			fcppt::chrono::duration<
				sanguis::time_unit
			>
		>
		(
			_time
		).count();
}
