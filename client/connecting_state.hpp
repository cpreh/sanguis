#ifndef SANGUIS_CLIENT_CONNECTING_STATE_HPP_INCLUDED
#define SANGUIS_CLIENT_CONNECTING_STATE_HPP_INCLUDED

#include "../tick_event.hpp"
#include "message_event.hpp"
#include "../messages/fwd.hpp"
#include "machine.hpp"
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/mpl/list.hpp>

namespace sanguis
{
namespace client
{
struct connecting_state 
	: public boost::statechart::simple_state<connecting_state,machine>
{
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<tick_event>,
		boost::statechart::custom_reaction<message_event> 
		> reactions;

	bool connected;

	connecting_state();
	boost::statechart::result react(const message_event &);
	boost::statechart::result react(const tick_event&);

	boost::statechart::result operator()(const messages::disconnect &);
	boost::statechart::result operator()(const messages::game_state &);
	boost::statechart::result operator()(const messages::connect &);
	boost::statechart::result handle_default_msg(const messages::base &);
};
}
}

#endif
