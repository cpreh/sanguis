#include "intermediate_state.hpp"
#include "connecting_state.hpp"
#include "running_state.hpp"
#include "../dispatch_type.hpp"
#include "../messages/game_state.hpp"
#include "../messages/disconnect.hpp"
#include "../messages/connect.hpp"
#include "../messages/client_info.hpp"
#include "../messages/types.hpp"
#include "../log_headers.hpp"
#include <sge/iconv.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/bind.hpp>
#include <typeinfo>
#include <ostream>

sanguis::client::connecting_state::connecting_state()
: connected(false)
{ 
}

boost::statechart::result
sanguis::client::connecting_state::react(
	message_event const &m)
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

boost::statechart::result
sanguis::client::connecting_state::handle_default_msg(
	messages::base const &m)
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1
			<< SGE_TEXT("received unexpected message ")
			<< sge::iconv(typeid(m).name()));
	return discard_event();
}

boost::statechart::result
sanguis::client::connecting_state::operator()(
	messages::disconnect const &)
{
	return transit<intermediate_state>();
}

boost::statechart::result
sanguis::client::connecting_state::operator()(
	messages::game_state const &m)
{
	post_event(
		message_event(
			messages::auto_ptr(
				new messages::game_state(
					m))));
	return transit<running_state>();
}

boost::statechart::result
sanguis::client::connecting_state::operator()(
	messages::connect const &)
{
	context<machine>().send(
		messages::auto_ptr(
			new messages::client_info(
				MESSAGE_TEXT("player1")))); // FIXME
	return discard_event();
}

boost::statechart::result
sanguis::client::connecting_state::react(
	tick_event const &)
{
	machine &m = context<machine>();
	m.dispatch();

	sge::string const status
		= connected
		? SGE_TEXT("waiting for gamestate")
		: SGE_TEXT("connecting");
	
	m.font().draw_text(
		status,
		sge::font::pos(0,0),
		sge::math::structure_cast<sge::font::size_type>(
			m.renderer()->screen_size()),
		sge::font::align_h::center,
		sge::font::align_v::center);

	return discard_event();
}
