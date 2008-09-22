#include "start_state.hpp"
#include "machine.hpp"
#include "intermediate_state.hpp"
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/states.hpp>

sanguis::client::start_state::start_state()
{}

boost::statechart::result
sanguis::client::start_state::react(
	tick_event const &)
{
	context<machine>().renderer()->set_state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::bool_::clear_zbuffer = true)
			(sge::renderer::state::float_::zbuffer_clear_val = 0)
	);

	return transit<intermediate_state>();
}
