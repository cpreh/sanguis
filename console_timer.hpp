#ifndef CONSOLE_TIMER_HPP_INCLUDED
#define CONSOLE_TIMER_HPP_INCLUDED

#include <sge/timer.hpp>
#include <sge/string.hpp>
#include <sge/su.hpp>
#include <sge/console/console.hpp>

class console_timer
{
	public:
	console_timer(const sge::string &,const sge::space_unit);
	sge::timer &v();
	private:
	sge::timer t;
	sge::con::action_var<sge::space_unit>::type var;

	sge::space_unit callback(const sge::space_unit,const sge::space_unit);
};

#endif
