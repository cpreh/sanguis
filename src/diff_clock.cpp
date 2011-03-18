#include "diff_clock.hpp"
#include <sge/time/duration.hpp>
#include <sge/time/second_f.hpp>
#include <fcppt/chrono/duration_impl.hpp>
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
	time_type const _diff
)
{
	diff_time_ +=
		sge::time::second_f(
			_diff
		).count();
}

sanguis::diff_clock::fun_type const
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
