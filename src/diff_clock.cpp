#include "diff_clock.hpp"
#include <sge/time/duration.hpp>
#include <sge/time/second_f.hpp>
#include <fcppt/chrono/duration_impl.hpp>
#include <fcppt/tr1/functional.hpp>

sanguis::diff_clock::diff_clock()
:
	diff_time(0)
{}

void sanguis::diff_clock::update(
	time_type const tm)
{
	diff_time +=
		sge::time::second_f(
			tm
		).count();
}

sanguis::diff_clock::fun_type const
sanguis::diff_clock::callback() const
{
	return std::tr1::bind(
		&diff_clock::time,
		this
	);
}

sge::time::unit
sanguis::diff_clock::time() const
{
	return diff_time;
}
