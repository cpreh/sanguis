#ifndef SANGUIS_CONSOLE_TIMER_HPP_INCLUDED
#define SANGUIS_CONSOLE_TIMER_HPP_INCLUDED

#include <sge/time/timer.hpp>
#include <sge/time/funit.hpp>
#include <sge/string.hpp>
#include <sge/console/action_var.hpp>
#include <boost/noncopyable.hpp>

class console_timer : boost::noncopyable {
public:
	console_timer(
		sge::string const &,
		sge::time::funit);
	sge::time::timer &v();
private:
	sge::time::timer t;
	sge::con::action_var<sge::time::funit>::type var;

	sge::time::funit
	callback(
		sge::time::funit,
		sge::time::funit);
};

#endif
