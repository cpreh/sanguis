#include "intermediate_state.hpp"
#include "connecting_state.hpp"
#include "machine.hpp"
#include "log.hpp"
#include <sge/log/headers.hpp>
#include <sge/text.hpp>
#include <sge/iconv.hpp>
#include <ostream>

sanguis::client::intermediate_state::intermediate_state(
	my_context ctx) 
  : my_base(ctx)
{}

boost::statechart::result
sanguis::client::intermediate_state::react(
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
sanguis::client::intermediate_state::react(
	tick_event const &)
{
	machine &m = context<machine>();
	m.dispatch();
	
	// show text in the screen center (hopefully)
	m.font().draw_text(
		SGE_TEXT("waiting for connect"),
		sge::font::pos(0,0),
		sge::math::structure_cast<sge::font::size_type>(
			m.renderer()->screen_size()),
		sge::font::align_h::center,
		sge::font::align_v::center);
	
	if (m.key_pressed(sge::input::kc::key_space))
	{
		m.connect();
		return transit<connecting_state>();
	}

	return discard_event();
}

sge::log::logger &
sanguis::client::intermediate_state::log()
{
	static sge::log::logger log_(
		client::log(),
		SGE_TEXT("intermediate_state: "));
	return log_;
}
