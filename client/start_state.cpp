#include "start_state.hpp"
#include "machine.hpp"
#include "intermediate_state.hpp"
#include <sge/iostream.hpp>
#include <sge/string.hpp>
#include <sge/media.hpp>
#include <sge/init.hpp>
#include <ostream>

sanguis::client::start_state::start_state()
{
	sge::clog << SGE_TEXT("client: entering start state\n");
}

boost::statechart::result sanguis::client::start_state::react(const tick_event&)
{
	sge::clog << SGE_TEXT("client: constructing persistent client data\n");

	// set renderer options
	context<machine>().renderer()->set_state(
		sge::renderer::state_list
			(sge::renderer::bool_state::clear_backbuffer = true)
	);

	return transit<intermediate_state>();
}
