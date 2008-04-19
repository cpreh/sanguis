#ifndef SANGUIS_SERVER_RUNNING_STATE_HPP_INCLUDED
#define SANGUIS_SERVER_RUNNING_STATE_HPP_INCLUDED

#include "machine.hpp"
#include "game_logic.hpp"
#include "message_event.hpp"
#include "../tick_event.hpp"

#include <boost/mpl/list.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/custom_reaction.hpp>

namespace sanguis
{
namespace server
{

class running_state
	: public boost::statechart::state<running_state,machine>
{
	public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<tick_event>,
		boost::statechart::custom_reaction<message_event> 
		> reactions;

	running_state(my_context);
	
	// statechart stuff
	boost::statechart::result react(const tick_event&);
	boost::statechart::result react(const message_event&);
	private:
	game_logic logic;
};

}
}

#endif
