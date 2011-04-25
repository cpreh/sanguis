#include "diff_clock.hpp"
#include "time_to_second.hpp"
#include <sge/time/second_f.hpp>
#include <fcppt/tr1/functional.hpp>

sanguis::diff_clock::diff_clock()
:
	diff_time_(0)
{
}

sanguis::diff_clock::~diff_clock()
{
}

void
sanguis::diff_clock::update(
	sanguis::time_delta const &_diff
)
{
	diff_time_ +=
		sge::time::second_f(
			sanguis::time_to_second(
				_diff
			)
		).count();
}

sge::time::callback const
sanguis::diff_clock::callback() const
{
	return
		std::tr1::bind(
			&diff_clock::time,
			this
		);
}

sge::time::unit
sanguis::diff_clock::time() const
{
	return diff_time_;
}
