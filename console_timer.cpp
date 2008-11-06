#include "console_timer.hpp"
#include <sge/time/second_f.hpp>
#include <sge/console/action_var_impl.hpp>
#include <boost/bind.hpp>

console_timer::console_timer(
	sge::string const &name,
	sge::time::funit const defval)
:
	t(sge::time::second_f(defval)),
	var(
		name,
		boost::bind(
			&console_timer::callback,
			this,
			_1,
			_2),
		defval)
{}

sge::time::timer &console_timer::v()
{
	return t;
}

sge::time::funit
console_timer::callback(
	sge::time::funit,
	sge::time::funit const newv)
{
	t.interval(
		sge::time::second_f(
			newv));
	return newv;
}
