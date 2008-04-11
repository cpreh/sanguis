#include "console_timer.hpp"
#include <boost/bind.hpp>

console_timer::console_timer(const sge::string &name,const sge::space_unit defval)
	: t(static_cast<sge::time_type>(static_cast<sge::space_unit>(sge::second())*defval)),
	  var(name,boost::bind(&console_timer::callback,this,_1,_2),defval) {}

sge::timer &console_timer::v() { return t; }

sge::space_unit console_timer::callback(const sge::space_unit,const sge::space_unit newv)
{
	t.interval(static_cast<sge::time_type>(static_cast<sge::space_unit>(sge::second())*newv));
	return newv;
}
