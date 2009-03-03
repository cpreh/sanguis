#include "intermediate.hpp"
#include "connecting.hpp"
#include "../machine.hpp"
#include "../log.hpp"
#include <sge/log/headers.hpp>
#include <sge/font/object.hpp>
#include <sge/font/text_size_t.hpp>
#include <sge/renderer/device.hpp>
#include <sge/text.hpp>
#include <sge/iconv.hpp>
#include <sge/structure_cast.hpp>
#include <ostream>

sanguis::client::states::intermediate::intermediate(
	my_context ctx) 
:
	my_base(ctx)
{}

boost::statechart::result
sanguis::client::states::intermediate::react(
	message_event const &m)
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1
			<< SGE_TEXT("got unexpected event ")
			<< sge::iconv(typeid(*m.message).name()));
	return defer_event();
}

boost::statechart::result
sanguis::client::states::intermediate::react(
	tick_event const &)
{
	machine &m = context<machine>();
	m.dispatch();
	
	// show text in the screen center (hopefully)
	m.font().draw_text(
		SGE_TEXT("waiting for connect"),
		sge::font::pos::null(),
		sge::structure_cast<
			sge::font::dim
		>(
			m.renderer()->screen_size()),
		sge::font::align_h::center,
		sge::font::align_v::center);
	
	if (m.key_pressed(sge::input::kc::key_space))
	{
		m.connect();
		return transit<connecting>();
	}

	return discard_event();
}

sge::log::logger &
sanguis::client::states::intermediate::log()
{
	static sge::log::logger log_(
		client::log(),
		SGE_TEXT("states::intermediate: "));
	return log_;
}
