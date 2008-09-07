#include "start_state.hpp"
#include "machine.hpp"
#include "intermediate_state.hpp"

sanguis::client::start_state::start_state()
{}

boost::statechart::result
sanguis::client::start_state::react(
	tick_event const &)
{
	// set renderer options
	context<machine>().renderer()->set_state(
		sge::renderer::state_list
			(sge::renderer::bool_state::clear_backbuffer = true)
	);

	return transit<intermediate_state>();
}
