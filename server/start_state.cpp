#include "start_state.hpp"
#include "waiting_state.hpp"

#include <sge/iostream.hpp>
#include <sge/string.hpp>

sanguis::server::start_state::start_state()
{
	sge::clog << SGE_TEXT("server: entering start state\n");
}

boost::statechart::result sanguis::server::start_state::react(const message_event&m)
{
	sge::clog << SGE_TEXT("server: got unexpected message: ") << typeid(*m.message).name() << SGE_TEXT("\n");
	return forward_event();
}

boost::statechart::result sanguis::server::start_state::react(const tick_event&)
{
	context<machine>().listen();
	return transit<waiting_state>(); 
}
