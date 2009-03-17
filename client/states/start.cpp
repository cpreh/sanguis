#include "start.hpp"
#include "menu.hpp"
#include "../machine.hpp"
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/states.hpp>
#include <sge/renderer/colors.hpp>
#include <sge/renderer/device.hpp>

sanguis::client::states::start::start()
{}

boost::statechart::result
sanguis::client::states::start::react(
	tick_event const &)
{
	context<machine>().renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::bool_::clear_zbuffer = false)
			(sge::renderer::state::color_::clear_color = sge::renderer::colors::black())
	);

	return transit<menu>();
}