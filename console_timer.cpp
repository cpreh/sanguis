#include "console_timer.hpp"
#include <sge/time/second.hpp>
#include <boost/bind.hpp>

console_timer::console_timer(const sge::string &name,const sge::space_unit defval)
	: t(sge::time::second(defval)),
	  var(name,boost::bind(&console_timer::callback,this,_1,_2),defval) {}

sge::time::timer &console_timer::v()
{
	return t;
}

sge::space_unit console_timer::callback(const sge::space_unit,const sge::space_unit newv)
{
	t.interval(
		sge::time::second(newv));
	return newv;
}
