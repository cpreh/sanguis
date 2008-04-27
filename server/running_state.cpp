#include "running_state.hpp"
#include "waiting_state.hpp"

#include <sge/iostream.hpp>
#include <ostream>

#include <boost/bind.hpp>

sanguis::server::running_state::running_state(my_context ctx)
	: my_base(ctx),
	  logic(boost::bind(&server::machine::send,&(context<machine>()),_1),
	  	boost::bind(&server::machine::console_print,&(context<machine>()),_1))
{
	sge::clog << SGE_TEXT("server: entering running state\n");
}

boost::statechart::result sanguis::server::running_state::react(const tick_event&t) 
{
	logic.update(t.delta());
	return discard_event();
}

boost::statechart::result sanguis::server::running_state::react(const message_event&m) 
{
	logic.process(m.id,*m.message);
	return logic.aborted()
		? transit<waiting_state>()
		: discard_event();
}
