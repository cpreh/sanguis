#include <sanguis/diff_clock.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/update_diff_clock.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/duration.hpp>
#include <fcppt/config/external_end.hpp>


void
sanguis::update_diff_clock(
	sanguis::diff_clock &_clock,
	sanguis::duration const &_duration
)
{
	_clock.update(
		boost::chrono::duration_cast<
			sanguis::diff_clock::duration
		>(
			_duration
		)
	);
}
