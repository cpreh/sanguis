#ifndef SANGUIS_SERVER_START_STATE_HPP_INCLUDED
#define SANGUIS_SERVER_START_STATE_HPP_INCLUDED

#include "machine.hpp"
#include "message_event.hpp"
#include "../tick_event.hpp"

#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>
#include <boost/mpl/list.hpp>

namespace sanguis
{
namespace server
{

struct start_state
	: public boost::statechart::simple_state<start_state,machine>
{
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<tick_event>,
		boost::statechart::custom_reaction<message_event> 
		> reactions;

	start_state();
	boost::statechart::result react(const tick_event&);
	boost::statechart::result react(const message_event&);
};

}
}

#endif
