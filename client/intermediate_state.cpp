#include "intermediate_state.hpp"
#include "connecting_state.hpp"
#include "machine.hpp"
#include <sge/iostream.hpp>
#include <sge/ostream.hpp>
#include <sge/string.hpp>

sanguis::client::intermediate_state::intermediate_state(my_context ctx) 
  : my_base(ctx)
{ 
	sge::clog << SGE_TEXT("client: entering intermediate state\n"); 
}

boost::statechart::result sanguis::client::intermediate_state::react(const message_event&m)
{
	sge::clog << SGE_TEXT("got unexpected event ") << typeid(*m.message).name() << SGE_TEXT("\n");
	return defer_event();
}

boost::statechart::result sanguis::client::intermediate_state::react(const tick_event&)
{
	sge::window::dispatch();
	
	machine &m = context<machine>();
	m.sys.input_system->dispatch();
	
	// show text in the screen center (hopefully)
	m.font.draw_text(SGE_TEXT("waiting for connect"),
		sge::font_pos(0,0),
		sge::font_dim(m.sys.renderer->screen_width(),
			m.sys.renderer->screen_height()),
		sge::font_align_h::center,sge::font_align_v::center);
	
	if (m.ks[sge::kc::key_space])
	{
		m.connect();
		return transit<connecting_state>();
	}

	return discard_event();
}
