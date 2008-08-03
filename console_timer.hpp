#ifndef SANGUIS_CONSOLE_TIMER_HPP_INCLUDED
#define SANGUIS_CONSOLE_TIMER_HPP_INCLUDED

#include <sge/time/timer.hpp>
#include <sge/string.hpp>
#include <sge/su.hpp>
#include <sge/console/action_var.hpp>
#include <boost/noncopyable.hpp>

class console_timer : boost::noncopyable
{
	public:
	console_timer(const sge::string &,const sge::space_unit);
	sge::time::timer &v();
	private:
	sge::time::timer t;
	sge::con::action_var<sge::space_unit>::type var;

	sge::space_unit callback(const sge::space_unit,const sge::space_unit);
};

#endif
