#include "intermediate_state.hpp"
#include "connecting_state.hpp"
#include "running_state.hpp"
#include "../dispatch_type.hpp"
#include "../messages/game_state.hpp"
#include "../messages/disconnect.hpp"
#include "../messages/connect.hpp"
#include "../messages/client_info.hpp"
#include "../messages/types.hpp"
#include <sge/string.hpp>
#include <sge/iostream.hpp>
#include <sge/ostream.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/bind.hpp>
#include <typeinfo>

sanguis::client::connecting_state::connecting_state() : connected(false)
{ 
	sge::clog << SGE_TEXT("client: entering connecting_state\n"); 
}

boost::statechart::result sanguis::client::connecting_state::react(const message_event &m)
{
	return dispatch_type<
		boost::mpl::vector<
			messages::disconnect,
			messages::connect,
			messages::game_state
		>,
		boost::statechart::result>(
		*this,
		*m.message,
		boost::bind(&connecting_state::handle_default_msg, this, _1));
}

boost::statechart::result sanguis::client::connecting_state::handle_default_msg(const messages::base &m)
{
	sge::cerr << SGE_TEXT("received unexpected message ") << typeid(m).name() << SGE_TEXT("\n");
	return discard_event();
}

boost::statechart::result sanguis::client::connecting_state::operator()(const messages::disconnect &)
{
	sge::clog << SGE_TEXT("client: disconnected\n");
	return transit<intermediate_state>();
}

boost::statechart::result sanguis::client::connecting_state::operator()(const messages::game_state &m)
{
	sge::clog << SGE_TEXT("client: received game state\n");
	post_event(
		message_event(
			messages::auto_ptr(
				new messages::game_state(
					m))));
	return transit<running_state>();
}

boost::statechart::result sanguis::client::connecting_state::operator()(const messages::connect &)
{
	sge::clog << SGE_TEXT("client: sending client info\n");
	context<machine>().send(
		messages::auto_ptr(
			new messages::client_info(
				MESSAGE_TEXT("player1"))));
	return discard_event();
}

boost::statechart::result sanguis::client::connecting_state::react(const tick_event&)
{
	sge::window::dispatch();

	machine &m = context<machine>();
	m.dispatch();

	sge::string const status = connected ? SGE_TEXT("waiting for gamestate") : SGE_TEXT("connecting");
	
	m.font().draw_text(
		status,
		sge::font::pos(0,0),
		sge::math::structure_cast<sge::font::size_type>(
			m.renderer()->screen_size()),
		sge::font::align_h::center,
		sge::font::align_v::center);

	return discard_event();
}
