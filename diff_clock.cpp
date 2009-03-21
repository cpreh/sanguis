#include "diff_clock.hpp"
#include <sge/time/time.hpp>
#include <boost/bind.hpp>

sanguis::diff_clock::diff_clock()
:
	diff_time(0)
{}

void sanguis::diff_clock::update(
	time_type const tm)
{
	diff_time += static_cast<sge::time::unit>(
		tm * static_cast<time_type>(sge::time::hz()));
}

sanguis::diff_clock::fun_type const
sanguis::diff_clock::callback() const
{
	return boost::bind(
		&diff_clock::time,
		this);
}

sge::time::unit
sanguis::diff_clock::time() const
{
	return diff_time;
}
